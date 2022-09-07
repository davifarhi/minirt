/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/07 15:49:28 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"

static void	make_cylinder_param(char **splitted, t_obj *cylinder)
{
	t_vector	*vector;
	t_cylinder	*newcylinder;

	vector = malloc(sizeof(t_vector));
	newcylinder = malloc(sizeof(t_cylinder));
	if (vector == NULL || newcylinder == NULL)
	{
		if (cylinder != NULL)
			free(cylinder);
		if (vector != NULL)
			free(vector);
		if (newcylinder != NULL)
			free(newcylinder);
		tabfree(splitted);
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	vector = split_vector_p(splitted, 2);
	newcylinder->vector = vector;
	newcylinder->diameter = ft_atof(splitted[3]);
	newcylinder->height = ft_atof(splitted[4]);
	cylinder->param = newcylinder;
}

static void	make_sphere_param(char **splitted, t_obj *sphere)
{
	double		*radius;

	radius = malloc(sizeof(double));
	if (radius == NULL)
	{
		if (sphere != NULL)
			free(sphere);
		tabfree(splitted);
		printf("Sphere parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	*radius = ft_atof(splitted[2]);
	sphere->param = radius;
}

static void	make_plan_param(char **splitted, t_obj *plan)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (vector == NULL)
	{
		if (plan != NULL)
			free(plan);
		tabfree(splitted);
		printf("Plan parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	vector = split_vector_p(splitted, 2);
	plan->param = vector;
}

void	create_volume(char **line, t_parse *setup, t_obj *volume, int type)
{
	char		**rgb;
	int			nbr;

	if (type == 5)
		nbr = 5;
	else
		nbr = 3;
	volume->type = type;
	volume->coord = split_coord_p(line, 1);
	rgb = ft_split(line[nbr], ',');
	if (rgb == NULL || tab_len(rgb) != 3)
		color_errors(line, rgb);
	volume->color = create_trgb(1, ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	tabfree(rgb);
	if (type == 5)
		make_cylinder_param(line, volume);
	else if (type == 4)
		make_plan_param(line, volume);
	else if (type == 3)
		make_sphere_param(line, volume);
	if (!setup->volumes)
		setup->volumes = ft_lstnew(volume);
	else
		ft_lstadd_back(&(setup->volumes), ft_lstnew(volume));
}

void	add_volume(char *line, t_parse *setup, int type)
{
	char		**splitted;
	t_obj		*volume;
	int			nbr;

	splitted = ft_split(line, ' ');
	volume = malloc(sizeof(t_obj));
	if (type == 5)
		nbr = 6;
	else
		nbr = 4;
	if (splitted == NULL || volume == NULL || tab_len(splitted) != nbr)
	{
		if (volume != NULL)
			free(volume);
		tabfree(splitted);
		printf("%s \n", enum_to_name(type));
		printf("parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		create_volume(splitted, setup, volume, type);
		tabfree(splitted);
	}
}

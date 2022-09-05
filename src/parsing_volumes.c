/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/05 20:21:41 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"

void	display_plan(t_list *list)
{
	if (list->content != NULL)
	{
		printf("type: %d\n", ((t_obj *)list->content)->type);
		printf("Coordonnées:\n");
		// printf("	x: %f\n", ((t_obj *)list->content)->coord.x);
		// printf("	y: %f\n", ((t_obj *)list->content)->coord.y);
		// printf("	z: %f\n", ((t_obj *)list->content)->coord.z);
		// printf("Color: %d\n", ((t_obj *)list->content)->color);
		// printf("Vector:\n");
		// printf("	x: %f\n", ((t_vector *)((t_obj *)list->content)->param)->x);
		// printf("	y: %f\n", ((t_vector *)((t_obj *)list->content)->param)->y);
		// printf("	z: %f\n", ((t_vector *)((t_obj *)list->content)->param)->z);
	}
}

t_coord	*split_coord_p(char **data, int index)
{
	char	**coord;
	t_coord	*newcoord;

	coord = ft_split(data[index], ',');
	newcoord = malloc(sizeof(t_coord));
	if (coord == NULL || tab_len(coord) != 3)
	{
		tabfree(data);
		tabfree(coord);
		printf("Format of coordonnee not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newcoord->x = ft_atof(coord[0]);
	newcoord->y = ft_atof(coord[1]);
	newcoord->z = ft_atof(coord[2]);
	tabfree(coord);
	return (newcoord);
}

t_vector	*split_vector_p(char **data, int index)
{
	char		**vector;
	t_vector	*newvector;

	vector = ft_split(data[index], ',');
	newvector = malloc(sizeof(t_vector));
	if (vector == NULL || tab_len(vector) != 3)
	{
		tabfree(data);
		tabfree(vector);
		printf("Format of vector data not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newvector->x = ft_atof(vector[0]);
	newvector->y = ft_atof(vector[1]);
	newvector->z = ft_atof(vector[2]);
	tabfree(vector);
	return (newvector);
}

void	add_plan(char *line, t_parse *setup)
{
	char		**splitted;
	char		**rgb;
	t_obj		*plan;
	t_list		*new;
	t_vector	*vector;

	splitted = ft_split(line, ' ');
	plan = malloc(sizeof(t_obj));
	vector = malloc(sizeof(t_vector));
	if (splitted != NULL && tab_len(splitted) == 4)
	{
		plan->type = Plan;
		plan->coord = split_coord_p(splitted, 1);
		vector = split_vector_p(splitted, 2);
		plan->param = vector;
		rgb = ft_split(splitted[3], ',');
		if (rgb == NULL || tab_len(rgb) != 3)
			color_errors(splitted, rgb);
		plan->color = create_trgb(1, ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		tabfree(splitted);
		tabfree(rgb);
	}
	else
	{
		tabfree(splitted);
		printf("Plan parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	// (void)new;
	(void)setup;
	new = ft_lstnew(plan);
	// display_plan(new);
	if (setup->volumes->content == NULL)
	{
		setup->volumes->content = new;
		setup->volumes->next = NULL;
	}
	else
		ft_lstadd_back(&(setup->volumes), new);
		// ft_lstadd_back((t_list **)(&(setup->volumes->content)), new);
	// ft_lstiter(setup->volumes, (void *)display_plan);
	// ft_lstiter(setup->volumes, (void *)display_plan);
	printf("____________________________________\n");
}

// ft_lstiter(setup->volumes, (void *)display_plan);
// printf("____________________________________\n");
// printf("%d\n", ((t_obj *)setup->volumes->content)->type);
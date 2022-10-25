/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/10/21 17:52:31 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"
#include "minirt_math.h"

static void	add_volume_to_list(char **line,
	t_parse *setup, t_obj *volume, int type)
{
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

static void	create_volume(char **line, t_parse *setup, t_obj *volume, int type)
{
	char		**rgb;
	int			nbr;

	if (type == 5)
		nbr = 5;
	else
		nbr = 3;
	volume->type = type;
	if (tab_len(line) == nbr + 2)
		volume->mirror = ft_atof(line[nbr + 1]);
	else
		volume->mirror = 0;
	if (volume->mirror != 0 && volume->mirror != 1)
		tabfree_exit("Error\nMirror param must be 0 or 1", line);
	volume->coord = split_coord_p(line, 1);
	rgb = ft_split(line[nbr], ',');
	if (rgb == NULL || tab_len(rgb) != 3 || colors_are_in_range(rgb))
		color_errors(line, rgb);
	volume->color = create_trgb(1, ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	tabfree(rgb);
	add_volume_to_list(line, setup, volume, type);
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
	if (splitted == NULL || volume == NULL
		|| (tab_len(splitted) != nbr && tab_len(splitted) != nbr + 1))
	{
		if (volume != NULL)
			free(volume);
		tabfree(splitted);
		printf("Error\n%s \n", enum_to_name(type));
		error_exit("parameters are not conform");
	}
	else
	{
		create_volume(splitted, setup, volume, type);
		tabfree(splitted);
	}
}

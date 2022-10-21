/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/10/21 17:08:36 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"
#include "minirt_math.h"

int	make_light_color(char **line, int len)
{
	char	**rgb;
	int		new;

	if (len == 3)
		new = create_trgb(1, 255, 255, 255);
	else if (len == 4)
	{
		rgb = ft_split(line[len - 1], ',');
		if (rgb == NULL || tab_len(rgb) != 3 || colors_are_in_range(rgb))
			color_errors(line, rgb);
		new = create_trgb(1, ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		tabfree(rgb);
	}
	else
		new = -1;
	return (new);
}

void	create_light(char **line, t_parse *setup, t_light *light)
{
	light->color = make_light_color(line, 4);
	light->coord = split_coord_p(line, 1);
	light->intensity = ft_atof(line[2]);
	if (light_is_in_range(light->intensity))
		error_exit("Error\nLight parameters are not in range 0-1");
	if (!setup->lights)
		setup->lights = ft_lstnew(light);
	else
		ft_lstadd_back(&(setup->lights), ft_lstnew(light));
}

void	add_lights(char *line, t_parse *setup)
{
	char	**splitted;
	t_light	*light;

	splitted = ft_split(line, ' ');
	light = malloc(sizeof(t_light));
	if (splitted == NULL || light == NULL || tab_len(splitted) != 4)
	{
		if (light != NULL)
			free(light);
		tabfree(splitted);
		printf("Error\nLight \n");
		error_exit("parameters are not conform");
	}
	else
	{
		create_light(splitted, setup, light);
		tabfree(splitted);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/11/09 13:48:30 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"
#include "minirt_math.h"

void	setup_init(t_parse	*setup)
{
	setup->is_there_cam = 0;
	setup->is_there_amb = 0;
	setup->is_there_light = 0;
	setup->lights = NULL;
	setup->volumes = NULL;
}

void	add_ambiant(char *line, t_parse *setup)
{
	char	**splitted;
	char	**rgb;

	if (setup->is_there_amb != 0)
		error_exit("Error\nToo much ambiant light in scene");
	setup->is_there_amb = 1;
	splitted = ft_split(line, ' ');
	if (splitted == NULL || tab_len(splitted) != 3)
		tabfree_exit("Error\nAmbient light parameters are not conform",
			splitted);
	setup->ambient_intensity = ft_atof(splitted[1]);
	if (light_is_in_range(setup->ambient_intensity))
		tabfree_exit("Error\nAmbiant parameters are not in range 0-1",
			splitted);
	rgb = ft_split(splitted[2], ',');
	if (rgb == NULL || tab_len(rgb) != 3 || colors_are_in_range(rgb))
		color_errors(splitted, rgb);
	setup->ambient_color = create_trgb(1, ft_atoi(rgb[0]),
			ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	tabfree(rgb);
	tabfree(splitted);
}

void	add_cam(char *line, t_parse *setup)
{
	char	**splitted;

	if (setup->is_there_cam != 0)
		error_exit("Error\nToo much cameras in scene");
	setup->is_there_cam = 1;
	splitted = ft_split(line, ' ');
	if (splitted != NULL && tab_len(splitted) == 4)
	{
		setup->cam_fov = ft_atoi(splitted[3]);
		if (fov_is_in_range(setup->cam_fov))
			tabfree_exit("Error\nCam fov parameter is not in range 0-180",
				splitted);
		setup->cam_v = split_vector(splitted, 2);
		setup->cam_coord = split_coord(splitted, 1);
		tabfree(splitted);
	}
	else
		tabfree_exit("Error\nCamera parameters are not conform",
			splitted);
}

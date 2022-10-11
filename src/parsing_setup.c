/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/10/11 11:19:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"

void	setup_init(t_parse	*setup)
{
	setup->is_there_cam = 0;
	setup->is_there_amb = 0;
	setup->is_there_light = 0;
	setup->volumes = NULL;
}

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

void	add_light(char *line, t_parse *setup)
{
	char	**splitted;

	if (setup->is_there_light != 0)
		error_exit("Error\nToo much lights in scene");
	setup->is_there_light = 1;
	splitted = ft_split(line, ' ');
	if (splitted != NULL && (tab_len(splitted) == 3 || tab_len(splitted) == 4))
	{
		setup->light_color = make_light_color(splitted, tab_len(splitted));
		setup->light_coord = split_coord(splitted, 1);
		setup->light_brightness = ft_atof(splitted[2]);
		tabfree(splitted);
		if (light_is_in_range(setup->light_brightness))
			error_exit("Error\nLight parameters are not in range 0-1");
	}
	else
		tabfree_exit("Error\nLight parameters are not conform",
			splitted);
}

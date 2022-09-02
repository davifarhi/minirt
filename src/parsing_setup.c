/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/02 15:42:03 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"

void	color_errors(char **splitted, char **rgb)
{
	tabfree(rgb);
	tabfree(splitted);
	printf("Format of colours not conform\n");
	printf("Format is: 250,250,250\n");
	printf("First for red, second for green and third for blue\n");
	exit(EXIT_FAILURE);
}

void	add_ambiant(char *line, t_parse *setup)
{
	char	**splitted;
	char	**rgb;

	if (setup->is_there_amb != 0)
	{
		printf("Too much ambiant light in scene\n");
		exit(EXIT_FAILURE);
	}
	setup->is_there_amb = 1;
	splitted = ft_split(line, ' ');
	if (splitted == NULL || tab_len(splitted) != 3)
	{
		printf("Ambient light parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	rgb = ft_split(splitted[2], ',');
	if (rgb == NULL || tab_len(rgb) != 3)
		color_errors(splitted, rgb);
	setup->ambient_intensity = ft_atof(splitted[1]);
	setup->ambient_int = create_trgb(1, atoi(rgb[0]),
			atoi(rgb[1]), atoi(rgb[2]));
	tabfree(rgb);
	tabfree(splitted);
}

void	add_cam(char *line, t_parse *setup)
{
	char	**splitted;

	if (setup->is_there_cam != 0)
	{
		printf("Too much cameras in scene\n");
		exit(EXIT_FAILURE);
	}
	setup->is_there_cam = 1;
	splitted = ft_split(line, ' ');
	if (splitted != NULL && tab_len(splitted) == 4)
	{
		setup->cam_coord = split_coord(splitted, 1);
		setup->cam_v = split_vector(splitted, 2);
		setup->cam_fov = ft_atoi(splitted[3]);
		tabfree(splitted);
	}
	else
	{
		tabfree(splitted);
		printf("Camera parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
}

void	add_light(char *line, t_parse *setup)
{
	char	**splitted;

	if (setup->is_there_light != 0)
	{
		printf("Too much lights in scene\n");
		exit(EXIT_FAILURE);
	}
	setup->is_there_light = 1;
	splitted = ft_split(line, ' ');
	if (splitted != NULL && tab_len(splitted) == 3)
	{
		setup->light_coord = split_coord(splitted, 1);
		setup->cam_fov = ft_atof(splitted[2]);
		tabfree(splitted);
	}
	else
	{
		tabfree(splitted);
		printf("Light parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
}

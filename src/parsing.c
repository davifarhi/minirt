/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/01 19:59:00 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

void	tabfree(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			if (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
	}
	if (tab != NULL)
	{
		free(tab);
		tab = NULL;
	}
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
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
	rgb = ft_split(splitted[2], ',');
	if (tab_len(rgb) != 3)
	{
		tabfree(rgb);
		tabfree(splitted);
		printf("Format of colours not conform\n");
		printf("Format is: 250,250,250\n");
		printf("First for red, second for green and third for blue\n");
		exit(EXIT_FAILURE);
	}
	setup->ambient_intensity = ft_atof(splitted[1]);
	setup->ambient_int = create_trgb(1, atoi(rgb[0]),
			atoi(rgb[1]), atoi(rgb[2]));
	tabfree(rgb);
	tabfree(splitted);
}

t_coord	split_coord(char **data, int index)
{
	char	**coord;
	t_coord	newcoord;

	coord = ft_split(data[index], ',');
	if (tab_len(coord) != 3)
	{
		tabfree(data);
		tabfree(coord);
		printf("Format of coordonnee not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newcoord.x = ft_atof(coord[0]);
	newcoord.y = ft_atof(coord[1]);
	newcoord.z = ft_atof(coord[2]);
	tabfree(coord);
	return (newcoord);
}

t_vector	split_vector(char **data, int index)
{
	char		**vector;
	t_vector	newvector;

	vector = ft_split(data[index], ',');
	if (tab_len(vector) != 3)
	{
		tabfree(data);
		tabfree(vector);
		printf("Format of vector data not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newvector.x = ft_atof(vector[0]);
	newvector.y = ft_atof(vector[1]);
	newvector.z = ft_atof(vector[2]);
	tabfree(vector);
	return (newvector);
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
	if (tab_len(splitted) == 4)
	{
		setup->cam_coord = split_coord(splitted, 1);
		setup->cam_v = split_vector(splitted, 2);
		setup->cam_fov = ft_atoi(splitted[3]);
	}
	tabfree(splitted);
}

void	add_light(char *line, t_parse *setup)
{
	(void)line;
	if (setup->is_there_light != 0)
	{
		printf("Too much lights in scene\n");
		exit(EXIT_FAILURE);
	}
	setup->is_there_light = 1;
}

void	parse_line(char *line, t_parse *setup)
{
	if (line == NULL)
		return ;
	if (ft_strnstr(line, "pl ", 3))
		printf("I'm a plan\n");
	else if (ft_strnstr(line, "sp ", 3))
		printf("I'm a sphere\n");
	else if (ft_strnstr(line, "cy ", 3))
		printf("I'm a cylinder\n");
	else if (ft_strnstr(line, "A ", 2))
		add_ambiant(line, setup);
	else if (ft_strnstr(line, "C ", 2))
		add_cam(line, setup);
	else if (ft_strnstr(line, "L ", 2))
		add_light(line, setup);
	else
	{
		printf("Unknown type of object in file! Use:\n");
		printf("A - Ambient light\n");
		printf("C - Camera\n");
		printf("L - Light\n");
		printf("pl - Plan\n");
		printf("sp - Sphere\n");
		printf("cy - Cylinder\n");
		exit(EXIT_FAILURE);
	}
}

void	mrt_parsing(char *file, t_parse *setup)
{
	char	*tmp;
	int		fd;

	setup->is_there_cam = 0;
	setup->is_there_amb = 0;
	setup->is_there_light = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("File is corrupted or does not exist\n");
		exit(EXIT_FAILURE);
	}
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		parse_line(tmp, setup);
		free(tmp);
		tmp = get_next_line(fd);
	}
}
// coord.x = 0;
// coord.y = 0;
// coord.z = 0;
// new.type = cam;
// new.coord = coord;
// new.color = 0;
// objects = ft_lstnew(&new);

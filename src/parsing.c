/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/05 16:07:02 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"
#include "get_next_line.h"

t_coord	split_coord(char **data, int index)
{
	char	**coord;
	t_coord	newcoord;

	coord = ft_split(data[index], ',');
	if (coord == NULL || tab_len(coord) != 3)
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
	if (vector == NULL || tab_len(vector) != 3)
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

static void	parse_line(char *line, t_parse *setup)
{
	if (line == NULL)
		return ;
	if (ft_strnstr(line, "pl ", 3))
		add_plan(line, setup);
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

static char	*clean_spaces(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strtrim(str, "\n");
	new = malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (new == NULL)
		return (NULL);
	while (tmp[i] != '\0')
	{
		if (ft_isspace(tmp[i]))
			new[i] = ' ';
		else
			new[i] = tmp[i];
		i++;
	}
	new[i] = '\0';
	ft_free(tmp);
	return (new);
}

void	mrt_parsing(char *file, t_parse *setup)
{
	char	*tmp;
	char	*cleaned;
	int		fd;

	setup->volumes = malloc(sizeof(t_list *));
	setup->volumes->content = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("File is corrupted or does not exist\n");
		exit(EXIT_FAILURE);
	}
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		if (*tmp != '\n')
		{
			cleaned = clean_spaces(tmp);
			parse_line(cleaned, setup);
			ft_free(cleaned);
		}
		ft_free(tmp);
		tmp = get_next_line(fd);
	}
	// display_plan((t_list *)setup->volumes->content);
	// display_plan((t_list *)setup->volumes->next);
	ft_lstiter(setup->volumes, (void *)display_plan);
	ft_free(tmp);
	close(fd);
}

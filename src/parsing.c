/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/21 15:42:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"
#include "get_next_line.h"

void	error_exit(char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

static void	parse_line(char *line, t_parse *setup)
{
	if (line == NULL)
		return ;
	if (ft_strnstr(line, "pl ", 3))
		add_volume(line, setup, Plan);
	else if (ft_strnstr(line, "sp ", 3))
		add_volume(line, setup, Sphere);
	else if (ft_strnstr(line, "cy ", 3))
		add_volume(line, setup, Cylinder);
	else if (ft_strnstr(line, "A ", 2))
		add_ambiant(line, setup);
	else if (ft_strnstr(line, "C ", 2))
		add_cam(line, setup);
	else if (ft_strnstr(line, "L ", 2))
		add_light(line, setup);
	else
	{
		printf("Error\nUnknown type of object in file! Use:\n");
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
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			new[i] = ' ';
		else
			new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

static char	*trimm_next_line(int fd)
{
	char	*trimmed;
	char	*tmp;

	tmp = get_next_line(fd);
	if (tmp == NULL)
		return (NULL);
	trimmed = ft_strtrim(tmp, "\n\t\v\f\r ");
	ft_free(tmp);
	return (trimmed);
}

void	mrt_parsing(char *file, t_parse *setup)
{
	char	*cleaned;
	char	*trimmed;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("Error\nFile is corrupted or does not exist");
	trimmed = trimm_next_line(fd);
	while (trimmed != NULL)
	{
		if (*trimmed != '\0' && *trimmed != '#')
		{
			cleaned = clean_spaces(trimmed);
			parse_line(cleaned, setup);
			ft_free(cleaned);
		}
		ft_free(trimmed);
		trimmed = trimm_next_line(fd);
	}
	ft_free(trimmed);
	close(fd);
}

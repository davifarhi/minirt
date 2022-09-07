/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/07 16:26:57 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"
#include "get_next_line.h"

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
	ft_free(tmp);
	close(fd);
}

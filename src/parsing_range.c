/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_range.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/21 15:57:49 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "free.h"
#include "parsing.h"

int	colors_are_in_range(char **rgb)
{
	if (!(ft_atoi(rgb[0]) >= 0 && ft_atoi(rgb[0]) <= 255))
		return (1);
	else if (!(ft_atoi(rgb[1]) >= 0 && ft_atoi(rgb[1]) <= 255))
		return (1);
	else if (!(ft_atoi(rgb[2]) >= 0 && ft_atoi(rgb[2]) <= 255))
		return (1);
	return (0);
}

void	color_errors(char **splitted, char **rgb)
{
	tabfree(rgb);
	tabfree(splitted);
	printf("Error\nFormat of colours not conform\n");
	printf("Format is: 255,255,255\n");
	printf("First for red, second for green and third for blue\n");
	printf("Every value must be in the range 0-255\n");
	exit(EXIT_FAILURE);
}

int	vector_is_in_range(t_vector vector)
{
	if (!(vector.x >= -1 && vector.x <= 1))
		return (1);
	else if (!(vector.y >= -1 && vector.y <= 1))
		return (1);
	else if (!(vector.z >= -1 && vector.z <= 1))
		return (1);
	return (0);
}

int	light_is_in_range(double light)
{
	if (!(light >= 0 && light <= 1))
		return (1);
	return (0);
}

int	fov_is_in_range(unsigned char fov)
{
	if (!(fov >= 0 && fov <= 180))
		return (1);
	return (0);
}

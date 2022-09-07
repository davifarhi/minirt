/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/07 16:14:50 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"

char	*enum_to_name(int type)
{
	if (type == 0)
		return ("Ambiant");
	else if (type == 1)
		return ("Camera");
	else if (type == 2)
		return ("Light");
	else if (type == 3)
		return ("Sphere");
	else if (type == 4)
		return ("Plan");
	else if (type == 5)
		return ("Cylinder");
	else
		return ("");
}

t_coord	*split_coord_p(char **data, int index)
{
	char	**coord;
	t_coord	*newcoord;

	coord = ft_split(data[index], ',');
	newcoord = malloc(sizeof(t_coord));
	if (coord == NULL || newcoord == NULL || tab_len(coord) != 3)
	{
		tabfree(data);
		tabfree(coord);
		if (newcoord != NULL)
			free(newcoord);
		printf("Format of coordonnee not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newcoord->x = ft_atof(coord[0]);
	newcoord->y = ft_atof(coord[1]);
	newcoord->z = ft_atof(coord[2]);
	tabfree(coord);
	return (newcoord);
}

t_vector	*split_vector_p(char **data, int index)
{
	char		**vector;
	t_vector	*newvector;

	vector = ft_split(data[index], ',');
	newvector = malloc(sizeof(t_vector));
	if (vector == NULL || newvector == NULL || tab_len(vector) != 3)
	{
		tabfree(data);
		tabfree(vector);
		if (newvector != NULL)
			free(newvector);
		printf("Format of vector data not conform\n");
		printf("Format is: x,y,z\n");
		exit(EXIT_FAILURE);
	}
	newvector->x = ft_atof(vector[0]);
	newvector->y = ft_atof(vector[1]);
	newvector->z = ft_atof(vector[2]);
	tabfree(vector);
	return (newvector);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/10/12 14:11:14 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"
#include "minirt_math.h"

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
		printf("Error\nFormat of coordonnee not conform\n");
		error_exit("Format is: x,y,z");
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
		error_exit("Error\nFormat of vector data not conform");
	}
	newvector->x = ft_atof(vector[0]);
	newvector->y = ft_atof(vector[1]);
	newvector->z = ft_atof(vector[2]);
	v_normalize(newvector);
	tabfree(vector);
	if (vector_is_in_range(*newvector))
	{
		if (newvector != NULL)
			free(newvector);
		tabfree_exit("Error\nVector not in range -1 to 1 or is 0,0,0", data);
	}
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
		printf("Error\nFormat of coordonnee not conform\n");
		error_exit("Format is: x,y,z");
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
		printf("Error\nFormat of vector data not conform\n");
		error_exit("Format is: x,y,z");
	}
	newvector.x = ft_atof(vector[0]);
	newvector.y = ft_atof(vector[1]);
	newvector.z = ft_atof(vector[2]);
	v_normalize(&newvector);
	tabfree(vector);
	if (vector_is_in_range(newvector))
		tabfree_exit("Error\nVector not in range -1 to 1 or is 0,0,0", data);
	return (newvector);
}

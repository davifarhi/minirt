/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/10/21 17:47:24 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"
#include "minirt_math.h"

void	make_cylinder_param(char **splitted, t_obj *cylinder)
{
	t_vector	*vector;
	t_cylinder	*newcylinder;

	newcylinder = malloc(sizeof(t_cylinder));
	if (newcylinder == NULL)
	{
		if (cylinder != NULL)
			free(cylinder);
		if (newcylinder != NULL)
			free(newcylinder);
		tabfree(splitted);
		printf("Error\n");
		exit(EXIT_FAILURE);
	}
	vector = split_vector_p(splitted, 2);
	newcylinder->vector = vector;
	newcylinder->diameter = ft_atof(splitted[3]);
	newcylinder->height = ft_atof(splitted[4]);
	cylinder->param = newcylinder;
}

void	make_sphere_param(char **splitted, t_obj *sphere)
{
	double		*radius;

	radius = malloc(sizeof(double));
	if (radius == NULL)
	{
		if (sphere != NULL)
			free(sphere);
		tabfree(splitted);
		error_exit("Error\nSphere parameters are not conform");
	}
	*radius = ft_atof(splitted[2]) / 2;
	sphere->param = radius;
}

void	make_plan_param(char **splitted, t_obj *plan)
{
	t_vector	*vector;

	vector = split_vector_p(splitted, 2);
	plan->param = vector;
}

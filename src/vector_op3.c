/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:52:14 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/20 13:22:41 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"
#include <math.h>
#include "minirt.h"

t_vector	cross_product(const t_vector *v1, const t_vector *v2)
{
	t_vector	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}

void	vector_rotate_x(t_vector *v, double x_angle)
{
	t_vector	v2;

	x_angle = calculate_degree_to_radians(x_angle);
	v2.x = v->x;
	v2.y = v->y * cos(x_angle) - v->z * sin(x_angle);
	v2.z = v->y * sin(x_angle) + v->z * cos(x_angle);
	*v = v2;
}

void	vector_rotate_y(t_vector *v, double y_angle)
{
	t_vector	v2;

	y_angle = calculate_degree_to_radians(y_angle);
	v2.x = v->x * cos(y_angle) + v->z * sin(y_angle);
	v2.y = v->y;
	v2.z = -v->x * sin(y_angle) + v->z * cos(y_angle);
	*v = v2;
}

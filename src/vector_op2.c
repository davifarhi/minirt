/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:28:18 by davifah           #+#    #+#             */
/*   Updated: 2022/10/10 12:49:26 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include <math.h>

double	dot_product(const t_vector v1, const t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	coord_to_vector(t_coord c)
{
	t_vector	v;

	v.x = c.x;
	v.y = c.y;
	v.z = c.z;
	return (v);
}

double	distance(const t_coord *c1, const t_coord *c2)
{
	t_coord	c;

	if (c1)
		c = *c1;
	else
	{
		c.x = 0;
		c.y = 0;
		c.z = 0;
	}
	return (sqrt(
			pow(c2->x - c.x, 2) + pow(c2->y - c.y, 2) + pow(c2->z - c.z, 2))
	);
}

t_vector	v_normalize(t_vector *v)
{
	double	d;

	d = distance(NULL, (t_coord *)v);
	if (d != 0)
		*v = v_div(*v, d);
	return (*v);
}

void	print_v(const t_vector v)
{
	printf("x %lf y %lf z %lf\n", v.x, v.y, v.z);
}

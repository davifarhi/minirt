/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:34:01 by davifah           #+#    #+#             */
/*   Updated: 2022/10/13 12:37:14 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>

/*
 *	Plane Math:
 *	n = (a, b, c) : plane normal vector
 *	P = (x, y, z) : given point of plane
 *	Po = (xo, yo, zo) : any point in plane (intersection)
 *	Po = A + bt : parametric equation of a line
 *
 * t = (a(x - Ax) + b(y - Ay) + c(z - Az)) / ((a * bx) + (b + by) + (c + bz))
*/

t_obj_ray_hit	*render_plane(const t_obj *obj,
		const t_coord *ray_origin, const t_vector *v_ray)
{
	t_obj_ray_hit	*obj_hit;
	double			t_param;
	double			denominator;

	denominator = dot_product(*(t_vector *)obj->param, *v_ray);
	if (!denominator)
		return (0);
	t_param = dot_product(*(t_vector *)obj->param,
			v_sub(*(t_vector *)obj->coord, *(t_vector *)ray_origin))
		/ denominator;
	if (t_param < 0)
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	obj_hit->obj = obj;
	return (obj_hit);
}

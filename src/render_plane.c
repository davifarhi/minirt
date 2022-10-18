/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:34:01 by davifah           #+#    #+#             */
/*   Updated: 2022/10/18 16:47:43 by dfarhi           ###   ########.fr       */
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

double	plane_intersection(t_vector pl_dir, t_coord pl_origin,
		t_vector ray_dir, t_coord ray_origin)
{
	double			t_param;
	double			denominator;

	denominator = dot_product(pl_dir, ray_dir);
	if (!denominator)
		return (-1000);
	t_param = dot_product(pl_dir, v_sub(*(t_vector *)&pl_origin,
				*(t_vector *)&ray_origin))
		/ denominator;
	return (t_param);
}

t_obj_ray_hit	*render_plane(const t_obj *obj,
		const t_coord *ray_origin, const t_vector *v_ray)
{
	t_obj_ray_hit	*obj_hit;
	double			t_param;

	t_param = plane_intersection(*(t_vector *)obj->param,
			*obj->coord, *v_ray, *ray_origin);
	if (t_param < 0)
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	obj_hit->obj = obj;
	return (obj_hit);
}

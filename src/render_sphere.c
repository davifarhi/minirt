/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/13 12:40:06 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>

/*
 *	Plane Math:
 *	P = (x, y, z) : center of the sphere
 *	r : radius
 *	Po = (xo, yo, zo) : any point in the sphere (intersection)
 *	Po = A + bt : parametric equation of a line
 *
 *	(bx² + by² + bz²)t² + 2(Ax*bx - bx*x + Ay*by - by*y + Azbz - bz*z)t +
 *		(Ax - x)² + (Ay - y)² + (Az - z)² - r² = 0
 *
 *	(b.b)t² + 2[(A.b) - (b.O)]t + ||A - O||² - r² = 0
*/

static t_quadratic_equation	sphere_get_quad_abc(
		const t_obj *obj, const t_coord *ray_origin, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_vector				v;

	v = v_sub(*(t_vector *)ray_origin, *(t_vector *)obj->coord);
	abc.a = dot_product(*v_ray, *v_ray);
	abc.b = 2 * (dot_product(*(t_vector *)ray_origin, *v_ray)
			- dot_product(*v_ray, *(t_vector *)obj->coord));
	abc.c = dot_product(v, v) - pow(*(double *)obj->param, 2);
	return (abc);
}

int	calculate_t_param_hit(const t_quadratic_equation *abc,
		double dis, double *t)
{
	double	t_1;
	double	t_2;

	t_1 = (-abc->b + sqrt(dis)) / (2 * abc->a);
	t_2 = (-abc->b - sqrt(dis)) / (2 * abc->a);
	if (t_1 < 0 && t_2 < 0)
		return (0);
	if (t_2 < 0)
		*t = t_1;
	else if (t_1 < 0)
		*t = t_2;
	else if (t_1 < t_2)
		*t = t_1;
	else if (t_2 < t_1)
		*t = t_2;
	else if (t_2 == t_1)
		*t = t_1;
	return (1);
}

t_obj_ray_hit	*render_sphere(const t_obj *obj,
		const t_coord *ray_origin, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					dis;
	double					t_param;

	abc = sphere_get_quad_abc(obj, ray_origin, v_ray);
	dis = calculate_discriminant(&abc);
	if (dis < 0 || !calculate_t_param_hit(&abc, dis, &t_param))
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	obj_hit->obj = obj;
	return (obj_hit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:17:20 by davifah           #+#    #+#             */
/*   Updated: 2022/10/18 16:19:09 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include "render.h"
#include <math.h>
#include "debug.h"

static t_quadratic_equation	cylinder_get_quad_abc(const t_obj *obj,
		const t_coord *ray_origin, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_vector				ref_v;
	t_vector				ref_p;

	ref_v = cross_product(v_ray, ((t_cylinder *)obj->param)->vector);
	ref_p = v_sub(*(t_vector *)ray_origin, *(t_vector *)obj->coord);
	abc.a = dot_product(ref_v, ref_v);
	abc.b = 2.f * dot_product(ref_v, cross_product(&ref_p,
				((t_cylinder *)obj->param)->vector));
	abc.c = dot_product(cross_product(&ref_p,
				((t_cylinder *)obj->param)->vector), cross_product
			(&ref_p, ((t_cylinder *)obj->param)->vector))
		- pow(((t_cylinder *)obj->param)->diameter / 2, 2);
	return (abc);
}

double	cylinder_limit_height(const t_coord *ray_origin,
		const t_obj *obj, const t_vector *v_ray, double t_int)
{
	t_vector	po;
	t_vector	cy_p;
	double		t;

	if (t_int < 0)
		return (-1);
	cy_p = v_add(*(t_vector *)obj->coord, v_mult(*((t_cylinder *)obj->param)
				->vector, ((t_cylinder *)obj->param)->height / 2));
	po = v_add(*(t_vector *)ray_origin, v_mult(*v_ray, t_int));
	t = sqrt(pow(distance((t_coord *)&po, (t_coord *)&cy_p), 2)
			- pow(((t_cylinder *)obj->param)->diameter / 2, 2));
	if (DEBUG_INFINITE_CY
		|| (0 <= t && t <= ((t_cylinder *)obj->param)->height / 2 && !isnan(t)))
		return (t_int);
	return (-1);
}

int	cylinder_calc_t_param_hit(double t[2])
{
	double	t_1;
	double	t_2;

	t_1 = t[0];
	t_2 = t[1];
	if (t_1 < 0 && t_2 < 0)
		return (0);
	if (t_2 < 0)
		return (1);
	else if (t_1 < 0)
		return (2);
	else if (t_1 < t_2)
		return (1);
	else if (t_2 < t_1)
		return (2);
	else
		return (1);
}

t_obj_ray_hit	*render_cylinder(const t_obj *obj,
		const t_coord *ray_origin, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					t_param[2];
	double					dis;

	abc = cylinder_get_quad_abc(obj, ray_origin, v_ray);
	dis = calculate_discriminant(&abc);
	t_param[0] = cylinder_limit_height(ray_origin, obj, v_ray,
			(-abc.b + sqrt(dis)) / (2 * abc.a));
	t_param[1] = cylinder_limit_height(ray_origin, obj, v_ray,
			(-abc.b - sqrt(dis)) / (2 * abc.a));
	if (dis < 0 || !cylinder_calc_t_param_hit(t_param))
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param[cylinder_calc_t_param_hit(t_param) - 1];
	obj_hit->obj = obj;
	return (obj_hit);
}

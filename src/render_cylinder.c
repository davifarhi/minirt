/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:17:20 by davifah           #+#    #+#             */
/*   Updated: 2022/10/10 13:28:28 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include "render.h"
#include <math.h>

/*
 * TODO
 * Fix horizontal (1, 0, 0) cylinders
 * Fix diagonal (1, 1, 0)
 * add limits to height
 */

static t_vector	delta_pos(const t_coord c1, const t_coord c2)
{
	t_vector	v;

	v.x = c1.x - c2.x;
	v.y = c1.y - c2.y;
	v.z = c1.z - c2.z;
	return (v);
}

static t_quadratic_equation	cylinder_get_quad_abc(const t_obj *obj,
		const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_vector				v1;
	t_vector				v2;

	v_normalize(((t_cylinder *)obj->param)->vector);
	/*
	t_quadratic_equation abc1;
	t_coord p = data->cam_coord;
	t_coord pa = *obj->coord;
	t_vector v = *v_ray;
	t_vector va = *((t_cylinder *)obj->param)->vector;
	int r = ((t_cylinder *)obj->param)->diameter / 2;
	t_vector delta_p = delta_pos(p, pa);
	t_vector				u1;
	t_vector				u2;

	u1 = v_sub(v, v_mult(va, dot_product(v, va)));
	u2 = v_sub(delta_p, v_mult(va, dot_product(delta_p, va)));
	abc1.a = dot_product(u1, u1);
	abc1.b = 2 * dot_product(u1, u2);
	abc1.c = dot_product(u2, u2) - pow(r, 2);
	*/

	v1 = v_sub(*v_ray, v_mult(*((t_cylinder *)obj->param)->vector,
				dot_product(*v_ray, *((t_cylinder *)obj->param)->vector)));
	v2 = v_sub(delta_pos(data->cam_coord, *obj->coord), v_mult(*((t_cylinder *)
					obj->param)->vector, dot_product(delta_pos(data->cam_coord,
						*obj->coord), *((t_cylinder *)obj->param)->vector)));
	abc.a = dot_product(v1, v1);
	abc.b = 2 * dot_product(v1, v2);
	abc.c = dot_product(v2, v2)
		- pow(((t_cylinder *)obj->param)->diameter / 2, 2);
	/*
	if (abc1.c != abc.c)
		printf("c different");
	if (abc1.b != abc.b)
		printf("b different");
	if (abc1.a != abc.a)
		printf("a different");
	if (u1.x != v1.x || u1.y != v1.y || u1.z != v1.z)
		printf("v1 different");
	if (u2.x != v2.x || u2.y != v2.y || u2.z != v2.z)
		printf("v2 different");
	*/
	//printf("x %lf y %lf z %lf dot2 %lf\n", v1.x, v1.y, v1.z, dot_product(v1, v1));
	return (abc);
}

double	cylinder_limit_height(const t_parse *data, const t_obj *obj, const t_vector *v_ray, double t_int)
{
	t_vector	po;
	t_vector	cy_v;
	double		t;

	if (t_int < 0)
		return (-1);
	cy_v = *((t_cylinder *)obj->param)->vector;
	v_normalize(&cy_v);
	po = v_add(coord_to_vector(data->cam_coord), v_mult(*v_ray, t_int));
	t = (dot_product(cy_v, po) - dot_product(cy_v, cy_v)) / dot_product(cy_v, cy_v);
	if (0 <= t && t <= ((t_cylinder *)obj->param)->height)
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

t_obj_ray_hit	*render_cylinder(const t_obj *obj, const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					t_param[2];
	double					dis;

	abc = cylinder_get_quad_abc(obj, data, v_ray);
	dis = calculate_discriminant(&abc);
	t_param[0] = cylinder_limit_height(data, obj, v_ray, (-abc.b + sqrt(dis)) / (2 * abc.a));
	t_param[1] = cylinder_limit_height(data, obj, v_ray, (-abc.b - sqrt(dis)) / (2 * abc.a));
	if (dis < 0 || !cylinder_calc_t_param_hit(t_param))
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param[cylinder_calc_t_param_hit(t_param) - 1];
	obj_hit->obj = obj;
	return (obj_hit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:17:20 by davifah           #+#    #+#             */
/*   Updated: 2022/10/05 21:40:56 by davifah          ###   ########.fr       */
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

double	dot_product(const t_vector v1, const t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	v_mult(const t_vector v1, double n)
{
	t_vector	v;

	v.x = v1.x * n;
	v.y = v1.y * n;
	v.z = v1.z * n;
	return (v);
}

t_vector	v_sub(const t_vector v1, const t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector	delta_pos(const t_coord c1, const t_coord c2)
{
	t_vector	v;

	v.x = c1.x - c2.x;
	v.y = c1.y - c2.y;
	v.z = c1.z - c2.z;
	return (v);
}

void print_v(const t_vector v)
{
	printf("x %lf y %lf z %lf\n", v.x, v.y, v.z);
}

static t_quadratic_equation	cylinder_get_quad_abc(const t_obj *obj,
		const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_vector				v1;
	t_vector				v2;

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

int	cylinder_calc_t_param_hit(const t_quadratic_equation *abc, double dis, double *t)
{
	double	t_1;
	double	t_2;

	t_1 = (-abc->b + sqrt(dis)) / (2 * abc->a);
	t_2 = (-abc->b - sqrt(dis)) / (2 * abc->a);
	if (t_1 < 0 && t_2 < 0)
		return (0);
	//printf("mine  - a %lf b %lf c %lf t1 %lf t2 %lf\n", abc->a, abc->b, abc->c, t_1, t_2);
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

t_obj_ray_hit	*render_cylinder(const t_obj *obj, const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					t_param;
	double					dis;

	abc = cylinder_get_quad_abc(obj, data, v_ray);
	dis = calculate_discriminant(&abc);
	if (dis < 0 || !cylinder_calc_t_param_hit(&abc, dis, &t_param))
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	//printf("t_cy %lf\n", t_param);
	obj_hit->obj = obj;
	return (obj_hit);
}

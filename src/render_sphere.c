/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 12:50:38 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>

t_quadratic_equation	sphere_get_quad_abc(
		const t_obj *obj, const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;

	abc.a = pow(v_ray->x, 2) + pow(v_ray->y, 2) + pow(v_ray->z, 2);
	abc.b = 2.0 * (
			v_ray->x * (data->cam_coord.x - obj->coord.x)
			+ v_ray->y * (data->cam_coord.y - obj->coord.y)
			+ v_ray->z * (data->cam_coord.z - obj->coord.z));
	abc.c = pow(data->cam_coord.x + obj->coord.x, 2)
		+ pow(data->cam_coord.y + obj->coord.y, 2)
		+ pow(data->cam_coord.z + obj->coord.z, 2)
		- pow(*((double *)obj->param), 2);
	return (abc);
}

t_obj	*create_sphere(t_coord coord, double radius, int color)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (0);
	obj->param = malloc(sizeof(double));
	if (!obj->param)
		return (0);
	obj->type = sphere;
	obj->coord = coord;
	obj->color = color;
	*(double *)obj->param = radius;
	return (obj);
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
		const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					dis;
	double					t_param;

	abc = sphere_get_quad_abc(obj, data, v_ray);
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

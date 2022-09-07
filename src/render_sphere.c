/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 11:56:58 by davifah          ###   ########.fr       */
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

t_obj	*create_sphere(double x, double y, double z, double radius)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (0);
	obj->param = malloc(sizeof(double));
	if (!obj->param)
		return (0);
	obj->type = sphere;
	obj->coord.x = x;
	obj->coord.y = y;
	obj->coord.z = z;
	obj->color = create_trgb(0, 255, 0, 0);
	*(double *)obj->param = radius;
	return (obj);
}

int	render_sphere(const t_obj *obj, const t_parse *data, const t_vector *v_ray)
{
	t_quadratic_equation	abc;
	double					dis;

	abc = sphere_get_quad_abc(obj, data, v_ray);
	dis = calculate_discriminant(&abc);
	if (dis >= 0)
		return (obj->color);
	return (0);
}
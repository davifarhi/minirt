/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/12 18:52:25 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include "lights.h"
#include <math.h>

int	calculate_t_param_hit(const t_quadratic_equation *abc,
		double dis, double *t);

t_quadratic_equation	sphere_get_quad_abc_s(
		const t_obj *obj, const t_parse *data, const t_vector *v_ray, t_coord point)
{
	t_quadratic_equation	abc;
	t_vector				v;

	(void)data;
	v = v_sub(*(t_vector *)(&point), *(t_vector *)obj->coord);
	abc.a = dot_product(*v_ray, *v_ray);
	abc.b = 2 * (dot_product(*(t_vector *)(&point), *v_ray)
			- dot_product(*v_ray, *(t_vector *)obj->coord));
	abc.c = dot_product(v, v) - pow(*(double *)obj->param, 2);
	return (abc);
}

t_obj_ray_hit	*render_sphere_s(const t_obj *obj,
		const t_parse *data, const t_vector *v_ray, t_coord point)
{
	t_quadratic_equation	abc;
	t_obj_ray_hit			*obj_hit;
	double					dis;
	double					t_param;

	abc = sphere_get_quad_abc_s(obj, data, v_ray, point);
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

t_obj_ray_hit	*render_plane_s(const t_obj *obj,
		const t_parse *data, const t_vector *v_ray, t_coord point)
{
	t_obj_ray_hit	*obj_hit;
	double			t_param;
	int			denominator;
	// t_vector		tmp;

	(void)data;
	denominator = ((t_vector *)obj->param)->x * v_ray->x
		+ ((t_vector *)obj->param)->y * v_ray->y
		+ ((t_vector *)obj->param)->z * v_ray->z;
	// printf("%f\n", denominator);
	if (!denominator)
		return (0);
	t_param = ((t_vector *)obj->param)->x * (obj->coord->x - point.x)
		+ ((t_vector *)obj->param)->y * (obj->coord->y - point.y)
		+ ((t_vector *)obj->param)->z * (obj->coord->z - point.z);
	t_param = t_param / denominator;
	if (t_param < 0)
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	obj_hit->obj = obj;
	return (obj_hit);
}

unsigned int	closest_obj(t_vector light_v, t_coord point, t_parse *data, t_vector normal)
{
	t_list			*tmp;
	t_obj_ray_hit	*obj_hit;
	float			t;

	tmp = data->volumes;
	v_normalize(&light_v);
	t = MAXFLOAT;
	point.x = point.x + normal.x;
	point.y = point.y + normal.y;
	point.z = point.z + normal.z;
	printf("%f\n", distance(NULL, &point));
	while (tmp)
	{
		obj_hit = 0;
		if (((t_obj *)tmp->content)->type == Sphere)
			obj_hit = render_sphere_s(tmp->content, data, &light_v, point);
		if (((t_obj *)tmp->content)->type == Plan)
			obj_hit = render_plane_s(tmp->content, data, &light_v, point);
		if (obj_hit != 0 && (*obj_hit).t > 0 && (*obj_hit).t < t)
			t = (*obj_hit).t;
		tmp = tmp->next;
		free(obj_hit);
	}
	if (t < MAXFLOAT)
	{
		return (0);
	}
	return (1);
}

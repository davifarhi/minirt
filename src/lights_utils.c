/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/11/09 11:21:47 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include "multithreading.h"
#include <math.h>

t_coord	hit_point(t_coord origin, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;

	point.x = origin.x + (obj_hit->t * v_ray.x);
	point.y = origin.y + (obj_hit->t * v_ray.y);
	point.z = origin.z + (obj_hit->t * v_ray.z);
	return (point);
}

static t_vector	vector_init(void)
{
	t_vector	vector;

	vector.x = 0;
	vector.y = 0;
	vector.z = 0;
	return (vector);
}

t_vector	cylinder_normal(t_coord point, t_obj_ray_hit *obj_hit)
{
	double		hypothenus;
	double		radius;
	double		dist;
	t_vector	c;

	radius = ((t_cylinder *)(obj_hit->obj->param))->diameter / 2;
	hypothenus = distance(&point, obj_hit->obj->coord);
	dist = sqrt(pow(hypothenus, 2) - pow(radius, 2));
	c = v_add(*(t_vector *)obj_hit->obj->coord,
			v_mult(*((t_cylinder *)(obj_hit->obj->param))->vector, dist));
	return (v_sub(*(t_vector *)&point, c));
}

t_vector	sphere_normal(t_coord point, const t_obj *obj)
{
	t_vector	v;

	v = v_sub(*(t_vector *)&point, *(t_vector *)obj->coord);
	if (distance(&point, obj->coord) < *(double *)obj->param)
		v = v_invert(&v);
	return (v);
}

t_vector	find_normal_vector(t_coord point, t_obj_ray_hit *obj_hit)
{
	t_vector	normal;
	float		dot;

	if (obj_hit->obj->type == Sphere)
		normal = sphere_normal(point, obj_hit->obj);
	else if (obj_hit->obj->type == Plan)
		normal = *((t_vector *)obj_hit->obj->param);
	else if (obj_hit->obj->type == Cylinder
		&& ((t_cylinder *)obj_hit->obj->param)->is_cap[thread_n_function(get, 0)] == 0)
		normal = cylinder_normal(point, obj_hit);
	else if (obj_hit->obj->type == Cylinder
		&& ((t_cylinder *)obj_hit->obj->param)->is_cap[thread_n_function(get, 0)] == 1)
	{
		dot = dot_product(v_sub(*(t_vector *)&point,
					*(t_vector *)obj_hit->obj->coord),
				*((t_cylinder *)obj_hit->obj->param)->vector);
		if (dot > -0.001 && dot < 0.001)
			normal = v_invert(((t_cylinder *)obj_hit->obj->param)->vector);
		else
			normal = *((t_cylinder *)obj_hit->obj->param)->vector;
	}
	else
		normal = vector_init();
	return (normal);
}

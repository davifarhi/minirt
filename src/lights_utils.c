/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/25 13:56:04 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
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

	print_v(*(t_vector *)&*((t_vector *)obj_hit->obj->coord));

	radius = ((t_cylinder *)(obj_hit->obj->param))->diameter / 2;
	hypothenus = distance(&point, obj_hit->obj->coord);
	dist = sqrt(pow(hypothenus, 2) - pow(radius, 2));
	c = v_add(*(t_vector *)&obj_hit->obj->coord,
			v_mult(*((t_cylinder *)(obj_hit->obj->param))->vector, dist));
	return (v_sub(*(t_vector *)&point, c));
}

t_vector	find_normal_vector(t_coord point, t_obj_ray_hit *obj_hit)
{
	t_vector	normal;

	if (obj_hit->obj->type == Sphere)
		normal = v_sub(*(t_vector *)&point, *(t_vector *)(obj_hit->obj->coord));
	else if (obj_hit->obj->type == Plan)
		normal = *((t_vector *)obj_hit->obj->param);
	else if (obj_hit->obj->type == Cylinder
		&& ((t_cylinder *)obj_hit->obj->param)->is_cap == 0)
		normal = cylinder_normal(point, obj_hit);
	else if (obj_hit->obj->type == Cylinder
		&& ((t_cylinder *)obj_hit->obj->param)->is_cap == 1)
	{
		if (dot_product(v_sub(*(t_vector *)&point,
					*(t_vector *)&obj_hit->obj->coord),
				*((t_cylinder *)obj_hit->obj->param)->vector) < -1)
			normal = v_invert(((t_cylinder *)obj_hit->obj->param)->vector);
		else
			normal = *((t_cylinder *)obj_hit->obj->param)->vector;
	}
	else
		normal = vector_init();
	return (normal);
}

float	make_light_len(t_coord point, t_coord light)
{
	float			additions;
	float			len;

	additions = pow((light.x - point.x), 2)
		+ pow((light.y - point.y), 2)
		+ pow((light.z - point.z), 2);
	len = sqrt(additions);
	return (len);
}

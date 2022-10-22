/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights_types.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/22 15:16:41 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>
#include <float.h>

float	spot_light(t_l_data l)
{
	double		scalaire;
	float		light_value;

	light_value = 0.0;
	scalaire = dot_product(l.normal, l.v_light);
	if (scalaire > 0)
	{
		light_value = (l.light.intensity * scalaire)
			/ distance(&(l.hit_point), l.light.coord);
	}
	return (light_value);
}

float	specular_light(t_l_data l, t_parse *data)
{
	t_vector	r;
	double		scalaire;
	float		light_value;
	t_vector	normal;
	t_coord		point;

	light_value = 0.0;
	point = hit_point(data->cam_coord, l.obj_hit, l.v_ray);
	normal = find_normal_vector(point, l.obj_hit);
	v_normalize(&normal);
	scalaire = dot_product(normal, l.v_light);
	r.x = (2 * normal.x * scalaire) - l.v_light.x;
	r.y = (2 * normal.y * scalaire) - l.v_light.y;
	r.z = (2 * normal.z * scalaire) - l.v_light.z;
	scalaire = dot_product(l.v_ray, r);
	if (scalaire < 0)
	{
		light_value = (l.light.intensity
				* (pow(scalaire / (distance(NULL, (t_coord *)(&r))
							* distance(NULL, (t_coord *)(&(l.v_ray)))), 50)));
	}
	return (light_value);
}

int	mirror_light(t_parse *data, t_l_data l, int old_value, t_vector v_ray)
{
	t_ray			mirror;
	double			scalaire;
	t_obj_ray_hit	*new_obj_hit;
	int				light_value;

	data->mirror_depth -= 1;
	scalaire = dot_product(l.normal, v_invert(&v_ray));
	mirror.vector.x = (2 * l.normal.x * scalaire) + v_ray.x;
	mirror.vector.y = (2 * l.normal.y * scalaire) + v_ray.y;
	mirror.vector.z = (2 * l.normal.z * scalaire) + v_ray.z;
	mirror.origin = l.hit_point;
	new_obj_hit = hit_obj(mirror.vector, data, l.hit_point);
	if (new_obj_hit != 0)
		light_value = render_light(data, new_obj_hit, mirror, old_value);
	else
		light_value = old_value;
	light_value = multiply_light(l.obj_hit->obj->color, 1, light_value);
	return (light_value);
}

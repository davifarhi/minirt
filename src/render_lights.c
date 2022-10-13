/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/13 23:40:16 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include <math.h>

t_coord	hit_point(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;

	point.x = data->cam_coord.x + (obj_hit->t * v_ray.x);
	point.y = data->cam_coord.y + (obj_hit->t * v_ray.y);
	point.z = data->cam_coord.z + (obj_hit->t * v_ray.z);
	return (point);
}

t_vector	find_normal_vector(t_parse *data, t_coord point, t_obj_ray_hit *obj_hit)
{
	t_vector	normal;

	(void)data;
	if (obj_hit->obj->type == Sphere)
	{
		normal.x = point.x - obj_hit->obj->coord->x;
		normal.y = point.y - obj_hit->obj->coord->y;
		normal.z = point.z - obj_hit->obj->coord->z;
	}
	else if (obj_hit->obj->type == Plan)
	{
		normal.x = point.x - ((t_vector *)obj_hit->obj->param)->x;
		normal.y = point.y - ((t_vector *)obj_hit->obj->param)->y;
		normal.z = point.z - ((t_vector *)obj_hit->obj->param)->z;
	}
	else
	{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
	}
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

int	spot_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;
	t_vector	normal;
	t_vector	light;
	double		scalaire;
	float		i;
	float		len;

	i = 0.0;
	point = hit_point(data, obj_hit, v_ray);
	normal = find_normal_vector(data, point, obj_hit);
	v_normalize(&normal);
	light.x = data->light_coord.x - point.x;
	light.y = data->light_coord.y - point.x;
	light.z = data->light_coord.z - point.z;
	scalaire = dot_product(normal, light);
	len = make_light_len(point, data->light_coord);
	if (scalaire > 0)
	{
		// NORMAL
		i = (data->light_brightness * scalaire)
			/ (pow(distance(NULL, (t_coord *)(&normal)), 2)
				* len);

	}
	if (obj_hit->obj->type == Sphere)
	{
		// SPECULAR
		t_vector r;
		r.x = (2 * normal.x * scalaire) - light.x;
		r.y = (2 * normal.y * scalaire) - light.y;
		r.z = (2 * normal.z * scalaire) - light.z;
		v_normalize(&r);
		double scalaire_s = dot_product(v_ray, r);
		if (scalaire_s < 0)
		{
			i += (data->light_brightness
				* (pow(scalaire_s / (distance(NULL, (t_coord *)(&r)) * distance(NULL, (t_coord *)(&v_ray))), 50)));
			if (i > 1)
				i = 1;
		}
	}
	return (mix_color(obj_hit->obj->color, i)
		* is_in_shadow(light, point, data, normal, obj_hit));
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	int	add_ambiant;
	int	add_light;

	add_light = spot_light(data, obj_hit, v_ray);
	add_ambiant = additive_light(add_light,
			data->ambient_intensity, data->ambient_color);
	return (add_ambiant);
}

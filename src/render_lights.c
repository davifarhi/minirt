/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 23:59:09 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include <math.h>
#include <float.h>

float	specular_light(t_parse *data, t_obj_ray_hit *obj_hit,
	t_vector v_ray, t_vector light)
{
	t_vector	r;
	t_vector	normal;
	double		scalaire;
	t_coord		point;
	float		light_value;

	light_value = 0.0;
	point = hit_point(data->cam_coord, obj_hit, v_ray);
	normal = find_normal_vector(point, obj_hit);
	v_normalize(&normal);
	scalaire = dot_product(normal, light);
	r.x = (2 * normal.x * scalaire) - light.x;
	r.y = (2 * normal.y * scalaire) - light.y;
	r.z = (2 * normal.z * scalaire) - light.z;
	scalaire = dot_product(v_ray, r);
	if (scalaire < 0)
	{
		light_value = (data->light_brightness
				* (pow(scalaire / (distance(NULL, (t_coord *)(&r))
							* distance(NULL, (t_coord *)(&v_ray))), 50)));
	}
	return (light_value);
}

float	spot_light(t_parse *data,
	t_coord point, t_vector normal, t_vector light)
{
	double		scalaire;
	float		light_value;

	light_value = 0.0;
	scalaire = dot_product(normal, light);
	if (scalaire > 0)
	{
		light_value = (data->light_brightness * scalaire)
			/ distance(&point, &data->light_coord);
	}
	return (light_value);
}

float	spot_light_test(t_l_data l)
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

float	specular_light_test(t_l_data l)
{
	t_vector	r;
	double		scalaire;
	float		light_value;

	light_value = 0.0;
	scalaire = dot_product(l.normal, l.v_light);
	r.x = (2 * l.normal.x * scalaire) - l.v_light.x;
	r.y = (2 * l.normal.y * scalaire) - l.v_light.y;
	r.z = (2 * l.normal.z * scalaire) - l.v_light.z;
	scalaire = dot_product(l.v_ray, r);
	if (scalaire < 0)
	{
		light_value = (l.light.intensity
				* (pow(scalaire / (distance(NULL, (t_coord *)(&r))
							* distance(NULL, (t_coord *)(&(l.v_ray)))), 50)));
	}
	return (light_value);
}

int	render_one_light(t_parse *data, t_l_data l, int i)
{
	int			light_value;
	float		light_indice;

	(void) i;
	(void) data;
	l.v_light = v_sub(*(t_vector *)&(l.light.coord),
			*(t_vector *)&(l.hit_point));
	// light_indice = spot_light_test(l);
	light_indice = spot_light_test(l);
	// if (i == 0)
		light_value = multiply_light(l.color, light_indice, l.light.color);
	// else
	// 	light_value = additive_light(l.color, light_indice, l.light.color);
	// light_indice = specular_light_test(l);
	// light_indice = specular_light(data, l.obj_hit, l.v_ray, l.v_light);
	// if (is_in_shadow(l.v_light, l.hit_point, data) != 0)
	// 	light_value = additive_light(light_value, light_indice, l.light.color);
	// else
	// 	light_value = l.previus;
	return (light_value);
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	int			light_value;
	t_l_data	l;
	t_list		*tmp;
	int			i;

	tmp = data->lights;
	i = 0;
	l.hit_point = hit_point(data->cam_coord, obj_hit, v_ray);
	l.normal = find_normal_vector(l.hit_point, obj_hit);
	v_normalize(&(l.normal));
	l.hit_point.x = l.hit_point.x - v_ray.x * LEN;
	l.hit_point.y = l.hit_point.y - v_ray.y * LEN;
	l.hit_point.z = l.hit_point.z - v_ray.z * LEN;
	l.v_ray = v_ray;
	l.obj_hit = obj_hit;
	l.previus = 0;
	l.color = obj_hit->obj->color;
	light_value = 0;
	while (tmp)
	{
		l.light = *(t_light *)(tmp->content);
		light_value = render_one_light(data, l, i);
		l.previus = light_value;
		l.color = light_value;
		tmp = tmp->next;
		i++;
	}
	light_value = additive_light(light_value,
			data->ambient_intensity, data->ambient_color);
	return (light_value);
}

// int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
// {
// 	int			light_value;
// 	float		light_indice;
// 	t_coord		point;
// 	t_vector	normal;
// 	t_vector	light;

// 	point = hit_point(data->cam_coord, obj_hit, v_ray);
// 	light = v_sub(*(t_vector *)&data->light_coord, *(t_vector *)&point);
// 	normal = find_normal_vector(point, obj_hit);
// 	v_normalize(&normal);
// 	point.x = point.x - v_ray.x * LEN;
// 	point.y = point.y - v_ray.y * LEN;
// 	point.z = point.z - v_ray.z * LEN;
// 	light_indice = spot_light(data, point, normal, light);
// 	light_value = multiply_light(obj_hit->obj->color,
// 			light_indice, data->light_color);
// 	light_indice = specular_light(data, obj_hit, v_ray, light);
// 	light_value = additive_light(light_value, light_indice, data->light_color)
// 		* is_in_shadow(light, point, data);
// 	light_value = additive_light(light_value,
// 			data->ambient_intensity, data->ambient_color);
// 	return (light_value);
// }

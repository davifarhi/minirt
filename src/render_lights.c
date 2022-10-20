/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 21:27:14 by mreymond         ###   ########.fr       */
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

static float	spot_light(t_parse *data,
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

float	spot_light_test(t_coord l_coord, double l_brightness,
	t_coord point, t_vector normal, t_vector light)
{
	double		scalaire;
	float		light_value;

	light_value = 0.0;
	scalaire = dot_product(normal, light);
	if (scalaire > 0)
	{
		light_value = (l_brightness * scalaire)
			/ distance(&point, &l_coord);
	}
	return (light_value);
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	int			light_value;
	float		light_indice;
	t_coord		point;
	t_vector	normal;
	t_vector	light;

	point = hit_point(data->cam_coord, obj_hit, v_ray);
	light = v_sub(*(t_vector *)&data->light_coord, *(t_vector *)&point);
	normal = find_normal_vector(point, obj_hit);
	v_normalize(&normal);
	point.x = point.x - v_ray.x * LEN;
	point.y = point.y - v_ray.y * LEN;
	point.z = point.z - v_ray.z * LEN;
	light_indice = spot_light(data, point, normal, light);
	light_value = multiply_light(obj_hit->obj->color,
			light_indice, data->light_color);
	light_indice = specular_light(data, obj_hit, v_ray, light);
	if (is_in_shadow(light, point, data) != 0)
		light_value = additive_light(light_value, light_indice, data->light_color);
	else	
		light_value = 0;

	t_coord			l_coord;
	double			l_brightness;
	int				l_color;
	int			old_value;
	old_value = light_value;
	l_coord.x = 25;
	l_coord.y = 75;
	l_coord.z = -95;
	l_brightness = 1;
	l_color = create_trgb(1, 0, 0, 255);
	light = v_sub(*(t_vector *)&l_coord, *(t_vector *)&point);
	light_indice = spot_light_test(l_coord, l_brightness, point, normal, light);
	light_value = additive_light(light_value, light_indice, l_color);
	light_indice = specular_light(data, obj_hit, v_ray, light);
	if (is_in_shadow(light, point, data) != 0)
		light_value = additive_light(light_value, light_indice, l_color);
	else	
		light_value = old_value;



	old_value = light_value;
	l_coord.x = 0;
	l_coord.y = 75;
	l_coord.z = -25;
	l_brightness = 1;
	l_color = create_trgb(1, 0, 255, 0);
	light = v_sub(*(t_vector *)&l_coord, *(t_vector *)&point);
	light_indice = spot_light_test(l_coord, l_brightness, point, normal, light);
	light_value = additive_light(light_value, light_indice, l_color);
	light_indice = specular_light(data, obj_hit, v_ray, light);
	if (is_in_shadow(light, point, data) != 0)
		light_value = additive_light(light_value, light_indice, l_color);
	else	
		light_value = old_value;


			
	
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/11 23:39:53 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include <math.h>

int	additive_light(int obj_color, float intensity, int ambiant_color)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = (get_r(obj_color) + get_r(ambiant_color)) * intensity;
	g = (get_g(obj_color) + get_g(ambiant_color)) * intensity;
	b = (get_b(obj_color) + get_b(ambiant_color)) * intensity;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

//trouver la coordonnée de la lumière
// trouver la coordonnée du point
// trouver le vecteur entre les 2. 

t_coord	sphere_hit_point(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;

	point.x = data->cam_coord.x + (obj_hit->t * v_ray.x);
	point.y = data->cam_coord.y + (obj_hit->t * v_ray.y);
	point.z = data->cam_coord.z + (obj_hit->t * v_ray.z);
	return (point);
}

t_vector	find_normal_vector(t_coord point, t_obj_ray_hit *obj_hit)
{
	t_vector	normal;

	if (obj_hit->obj->type == Sphere)
	{
		normal.x = point.x - obj_hit->obj->coord->x;
		normal.y = point.y - obj_hit->obj->coord->y;
		normal.z = point.z - obj_hit->obj->coord->z;
	}
	else if (obj_hit->obj->type == Plan)
	{
		normal.x = ((t_vector *)obj_hit->obj->param)->x;
		normal.y = ((t_vector *)obj_hit->obj->param)->y;
		normal.z = ((t_vector *)obj_hit->obj->param)->z;
	}
	else
	{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
	}
	return (normal);
}

int	make_light_len(t_coord point, t_coord light)
{
	int			additions;
	int			len;

	additions = pow((light.x - point.x), 2)
		+ pow((light.y - point.y), 2)
		+ pow((light.z - point.z), 2);
	len = sqrt(additions);
	return (len);
}

int	mix_color(int color, float i)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = get_r(color) * i;
	g = get_g(color) * i;
	b = get_b(color) * i;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

int	spot_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;
	t_vector	normal;
	t_vector	light;
	int			scalaire;
	float		i;

	i = 0.0;
	point = sphere_hit_point(data, obj_hit, v_ray);
	normal = find_normal_vector(point, obj_hit);
	v_normalize(&normal);
	light.x = data->light_coord.x - point.x;
	light.y = data->light_coord.y - point.x;
	light.z = data->light_coord.z - point.z;
	scalaire = dot_product(light, normal);
	if (scalaire > 0)
	{
		i = (data->light_brightness * scalaire)
			/ (pow(distance(NULL, (t_coord *)(&normal)), 2)
				* make_light_len(point, data->light_coord));
	}
	return (mix_color(obj_hit->obj->color, i));
}

int	multiply_light(int obj_color, float intensity, int ambiant_color)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = ((get_r(obj_color) * get_r(ambiant_color)) / 255) * intensity;
	g = ((get_g(obj_color) * get_g(ambiant_color)) / 255) * intensity;
	b = ((get_b(obj_color) * get_b(ambiant_color)) / 255) * intensity;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	int	add_ambiant;
	int	add_light;

	add_light = spot_light(data, obj_hit, v_ray);
	// (void) v_ray;
	// add_light = obj_hit->obj->color;
	add_ambiant = multiply_light(add_light,
			data->ambient_intensity, data->ambient_color);
	return (add_ambiant);
}

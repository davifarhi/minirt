/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/05 18:58:18 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
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


int	spot_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		dot;
	t_vector	normal;
	t_vector	light;
	int			scalaire;
	float		i;
	int			additions;
	int			len;
	// int			color;
	int	r;
	int	g;
	int	b;
	int	mix;

	i = 0.0;
	dot.x = data->cam_coord.x + (obj_hit->t * v_ray.x);
	dot.y = data->cam_coord.y + (obj_hit->t * v_ray.y);
	dot.z = data->cam_coord.z + (obj_hit->t * v_ray.z);
	normal.x = dot.x - obj_hit->obj->coord->x;
	normal.y = dot.y - obj_hit->obj->coord->y;
	normal.z = dot.z - obj_hit->obj->coord->z;
	light.x = data->light_coord.x - dot.x;
	light.y = data->light_coord.y - dot.x;
	light.z = data->light_coord.z - dot.z;
	scalaire = (normal.x * light.x)
		+ (normal.y * light.y) + (normal.z * light.z);
	additions = pow((data->light_coord.x - dot.x), 2)
		+ pow((data->light_coord.y - dot.y), 2)
		+ pow((data->light_coord.z - dot.z), 2);
	len = sqrt(additions);
	if (scalaire > 0)
	{
		i = (data->light_brightness * scalaire)
			/ (pow(*((double *)(obj_hit->obj)->param), 2) * len);
	}
	// color = obj_hit->obj->color * i;
	r = get_r(obj_hit->obj->color) * i;
	g = get_g(obj_hit->obj->color) * i;
	b = get_b(obj_hit->obj->color) * i;
	mix = create_trgb(1, r, g, b);
	return (mix);
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
	add_ambiant = multiply_light(add_light,
			data->ambient_intensity, data->ambient_color);
	return (add_ambiant);
}

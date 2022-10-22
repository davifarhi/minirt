/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/22 15:16:16 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>
#include <float.h>

int	render_one_light(t_parse *data, t_l_data l, int i)
{
	int			light_value;
	float		light_indice;

	l.v_light = v_sub(*(t_vector *)(l.light.coord),
			*(t_vector *)&(l.hit_point));
	light_indice = spot_light(l);
	if (i == 0)
		light_value = multiply_light(l.obj_hit->obj->color,
				light_indice, l.light.color);
	else
	{
		light_value = additive_light(l.color, light_indice, l.light.color);
		light_value = multiply_light(l.obj_hit->obj->color, 1, light_value);
	}
	light_indice = specular_light(l, data);
	if (is_in_shadow(l.v_light, l.hit_point, data, *l.light.coord) != 0)
		light_value = additive_light(light_value, light_indice, l.light.color);
	else
		light_value = l.previus;
	light_value = additive_light(light_value,
			data->ambient_intensity, data->ambient_color);
	return (light_value);
}

int	lights_loop(t_parse *data, t_l_data l)
{
	t_list		*tmp;
	int			light_value;
	int			i;

	i = 0;
	light_value = 0;
	tmp = data->lights;
	while (tmp)
	{
		l.light = *(t_light *)(tmp->content);
		if (l.light.intensity > 0)
		{
			light_value = render_one_light(data, l, i);
			l.previus = light_value;
			l.color = light_value;
		}
		tmp = tmp->next;
		i++;
	}
	if (light_value == 0)
		light_value = multiply_light(l.color,
				data->ambient_intensity, data->ambient_color);
	return (light_value);
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_ray ray, int color)
{
	int			light_value;
	t_l_data	l;

	l.hit_point = hit_point(ray.origin, obj_hit, ray.vector);
	l.normal = find_normal_vector(l.hit_point, obj_hit);
	v_normalize(&(l.normal));
	l.hit_point.x = l.hit_point.x - ray.vector.x * LEN;
	l.hit_point.y = l.hit_point.y - ray.vector.y * LEN;
	l.hit_point.z = l.hit_point.z - ray.vector.z * LEN;
	l.obj_hit = obj_hit;
	l.previus = 0;
	l.color = color;
	l.v_ray = ray.vector;
	light_value = lights_loop(data, l);
	if ((obj_hit->obj->mirror == 1 && data->mirror_depth > 0))
		light_value = mirror_light(data, l, light_value, ray.vector);
	return (light_value);
}

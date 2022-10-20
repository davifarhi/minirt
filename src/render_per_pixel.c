/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_per_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:58:52 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 17:49:40 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "lights.h"
#include "debug.h"

static void	new_obj_hit(t_obj_ray_hit **obj_hit, t_obj_ray_hit *obj_new)
{
	if (!obj_new)
		return ;
	if (!*obj_hit)
		*obj_hit = obj_new;
	else
	{
		if ((*obj_hit)->t > obj_new->t)
		{
			free(*obj_hit);
			*obj_hit = obj_new;
		}
		else
			free(obj_new);
	}
}

void	calculate_intersection(
		const t_vector *v_ray, t_parse *data, unsigned int *color)
{
	t_list			*tmp;
	t_obj_ray_hit	*obj_hit;

	tmp = data->volumes;
	obj_hit = 0;
	while (tmp)
	{
		if (((t_obj *)tmp->content)->type == Sphere)
			new_obj_hit(&obj_hit, render_sphere(tmp->content,
					&data->cam_coord, v_ray));
		if (((t_obj *)tmp->content)->type == Plan)
			new_obj_hit(&obj_hit, render_plane(tmp->content,
					&data->cam_coord, v_ray));
		if (((t_obj *)tmp->content)->type == Cylinder)
			new_obj_hit(&obj_hit, render_cylinder(tmp->content,
					&data->cam_coord, v_ray));
		tmp = tmp->next;
	}
	if (obj_hit)
	{
		*color = render_light(data, obj_hit, *v_ray);
		if (DEBUG_LIGHT_OFF)
			*color = obj_hit->obj->color;
		free(obj_hit);
	}
}

unsigned int	render_per_pixel(int x, int y, t_parse *data)
{
	t_vector		v_ray;
	unsigned int	color;

	v_ray = render_get_camera_direction(data->cam_v, data->render, x, y);
	color = 0;
	calculate_intersection(&v_ray, data, &color);
	render_antialiasing(x, y, &v_ray, data);
	return (aa_color_average(color, data->render, x, y));
}

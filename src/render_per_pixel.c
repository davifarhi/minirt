/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_per_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:58:52 by davifah           #+#    #+#             */
/*   Updated: 2022/09/30 15:33:35 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

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

unsigned int	render_per_pixel(int x, int y, t_parse *data)
{
	t_list			*tmp;
	t_vector		v_ray;
	t_obj_ray_hit	*obj_hit;
	int				color;

	tmp = data->volumes;
	v_ray = render_get_camera_direction(data->cam_v, data->render, x, y);
	obj_hit = 0;
	while (tmp)
	{
		if (((t_obj *)tmp->content)->type == Sphere)
			new_obj_hit(&obj_hit, render_sphere(tmp->content, data, &v_ray));
		if (((t_obj *)tmp->content)->type == Plan)
			new_obj_hit(&obj_hit, render_plane(tmp->content, data, &v_ray));
		tmp = tmp->next;
	}
	color = 0;
	if (obj_hit)
	{
		color = obj_hit->obj->color;
		free(obj_hit);
	}
	return (color);
}

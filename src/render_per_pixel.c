/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_per_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:58:52 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 12:59:23 by davifah          ###   ########.fr       */
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

static void	configure_data(t_parse *data)
{
	t_list	*new;
	t_coord	c;

	c.x = 0;
	c.y = 1;
	c.z = -8;
	data->volumes = ft_lstnew(create_sphere(c, 1, create_trgb(1, 255, 0, 0)));
	c.x = 0;
	c.y = 0;
	c.z = -9;
	new = ft_lstnew(create_sphere(c, 2, create_trgb(1, 0, 255, 0)));
	ft_lstadd_back(&data->volumes, new);
	data->cam_coord.x = 0;
	data->cam_coord.y = 0;
	data->cam_coord.z = 0;
	data->cam_v.x = 0;
	data->cam_v.y = 0;
	data->cam_v.z = -1;
}

unsigned int	render_per_pixel(int x, int y, t_parse *data)
{
	t_list			*tmp;
	t_vector		v_ray;
	t_obj_ray_hit	*obj_hit;
	int				color;

	if (!x && !y)
	{
		configure_data(data);
	}
	tmp = data->volumes;
	v_ray = render_get_camera_direction(data->cam_v, data->render, x, y);
	obj_hit = 0;
	while (tmp)
	{
		if (((t_obj *)tmp->content)->type == sphere)
			new_obj_hit(&obj_hit, render_sphere(tmp->content, data, &v_ray));
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

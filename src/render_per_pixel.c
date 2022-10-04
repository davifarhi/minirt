/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_per_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 12:58:52 by davifah           #+#    #+#             */
/*   Updated: 2022/10/04 17:56:31 by mreymond         ###   ########.fr       */
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

int	ambiant_making(int obj_color, float intensity)
{
	int	r;
	int	g;
	int	b;

	r = get_r(obj_color);
	g = get_g(obj_color);
	b = get_b(obj_color);
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
		color = data->ambient_intensity * obj_hit->obj->color;
		printf("%d\n", color);
		free(obj_hit);
	}
	return (color);
}

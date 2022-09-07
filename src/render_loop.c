/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 12:53:31 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "debug.h"
#include "render.h"

static int	render_loop(t_parse *data);
static void	put_img_to_win(t_mlx *mlx);

void	new_obj_hit(t_obj_ray_hit **obj_hit, t_obj_ray_hit *obj_new)
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

int	looper_mlx(void *param)
{
	int	c;

	c = -1;
	while (!render_loop(param) && (!LINE_BY_LINE_RENDER
			|| ++c < (int)((t_parse*)param)->render->res_width))
		continue ;
	return (0);
}

static int	render_loop(t_parse *data)
{
	static int	x = -1;
	static int	y = 0;

	if (++x >= (int)data->render->res_width)
	{
		x = 0;
		y++;
		if (LINE_BY_LINE_RENDER)
			put_img_to_win(&data->mlx);
	}
	if (y >= (int)data->render->res_height)
	{
		if (x < 0)
			return (1);
		if (!LINE_BY_LINE_RENDER)
			put_img_to_win(&data->mlx);
		if (DEBUG_LOOP_FINISHED)
			ft_putstr_fd("Finished\n", 2);
		x = -3;
		return (1);
	}
	if (DEBUG_LOOP_PIXEL)
		printf("rendering pixel x %d - y %d\n", x, y);
	ft_pixel_put(&data->mlx, x, y, render_per_pixel(x, y, data));
	return (0);
}

static void	put_img_to_win(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

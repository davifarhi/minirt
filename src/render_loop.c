/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/11/09 10:15:18 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "debug.h"
#include "render.h"

static int	render_loop(t_parse *data);
static void	put_img_to_win(t_mlx *mlx);

int	looper_mlx(void *param)
{
	int	c;

	c = -1;
	while (!render_loop(param) && (!LINE_BY_LINE_RENDER
			|| ++c < (int)((t_parse*)param)->render->res_width - 1))
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
		render_time();
		x = -3;
		return (1);
	}
	if (!x && !y)
		render_time();
	ft_pixel_put(&data->mlx, x, y, render_per_pixel(x, y, data));
	return (0);
}

static void	put_img_to_win(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:09:55 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "debug.h"
#include "render.h"

static int	render_loop(void *param);
static void	put_img_to_win(t_mlx *mlx);

unsigned int	render_per_pixel(int x, int y, void *param)
{
	t_vector	v;

	v.x = 3;
	v.y = -1;
	v.z = -4;
	render_get_camera_direction(&v, x, y);
	(void)param;
	return (create_trgb(255, (int)((float)x / RESOLUTION_X * 255.0f),
		(int)((float)y / RESOLUTION_Y * 255.0f), 0));
}

int	looper_mlx(void *param)
{
	int	ret;
	int	c;

	ret = render_loop(param);
	c = -1;
	while (!ret && (!LINE_BY_LINE_RENDER || ++c < RESOLUTION_X))
		ret = render_loop(param);
	return (0);
}

static int	render_loop(void *param)
{
	static int	x = -1;
	static int	y = 0;

	if (++x >= RESOLUTION_X)
	{
		x = 0;
		y++;
		if (LINE_BY_LINE_RENDER)
			put_img_to_win((t_mlx *)param);
	}
	if (y >= RESOLUTION_Y)
	{
		if (x < 0)
			return (1);
		if (!LINE_BY_LINE_RENDER)
			put_img_to_win((t_mlx *)param);
		if (DEBUG_LOOP_FINISHED)
			ft_putstr_fd("Finished\n", 2);
		x = -3;
		return (1);
	}
	if (DEBUG_LOOP_PIXEL)
		printf("rendering pixel x %d - y %d\n", x, y);
	ft_pixel_put((t_mlx *)param, x, y, render_per_pixel(x, y, param));
	return (0);
}

static void	put_img_to_win(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

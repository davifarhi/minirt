/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/08/31 17:06:11 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "debug.h"

static int	render_loop(void *param);

unsigned int	render_per_pixel(int x, int y, void *param)
{
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
	while (!ret && ++c < RESOLUTION_X)
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
		mlx_put_image_to_window(((t_mlx *)param)->mlx, ((t_mlx *)param)->win,
			((t_mlx *)param)->img.img, 0, 0);
	}
	if (y >= RESOLUTION_Y)
	{
		if (y == RESOLUTION_Y)
		{
			y++;
			if (DEBUG_LOOP_FINISHED)
				ft_putstr_fd("Finished\n", 2);
		}
		return (1);
	}
	if (DEBUG_LOOP_PIXEL)
		printf("rendering pixel x %d - y %d\n", x, y);
	ft_pixel_put((t_mlx *)param, x, y, render_per_pixel(x, y, param));
	return (0);
}

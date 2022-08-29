/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:04:14 by davifah           #+#    #+#             */
/*   Updated: 2022/08/29 12:03:04 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"

static int	win_close(int code, void *param);
static int	deal_key(int key, void *param);

t_mlx	mlx_setup(void)
{
	t_mlx	mlx;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, RESOLUTION_X, RESOLUTION_Y, "minirt");
	mlx_hook(mlx.win, 17, 1L << 0, win_close, (void *)&mlx);
	mlx_key_hook(mlx.win, deal_key, (void *)&mlx);
	mlx.img.img = mlx_new_image(mlx.mlx, RESOLUTION_X, RESOLUTION_Y);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img, &mlx.img.bpp,
			&mlx.img.line_len, &mlx.img.endian);
	fill_image(&mlx, create_trgb(1, 65, 105, 225));
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (mlx);
}

static int	deal_key(int key, void *param)
{
	if (key == ESC_KEY)
	{
		printf("Escape pressed, quitting_program...\n");
		mlx_destroy_window(((t_mlx *)param)->mlx, ((t_mlx *)param)->win);
		exit(0);
	}
	return (0);
}

static int	win_close(int code, void *param)
{
	printf("Quitting program...\n");
	exit(0);
	(void)param;
	(void)code;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:04:14 by davifah           #+#    #+#             */
/*   Updated: 2022/08/31 17:02:20 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "render.h"

static int	on_win_close(int code, void *param);
static int	deal_key(int key, void *param);

int	mlx_setup(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
	{
		perror("mlx_init");
		return (1);
	}
	mlx->win = mlx_new_window(mlx->mlx, RESOLUTION_X, RESOLUTION_Y, "minirt");
	if (!mlx->win)
	{
		perror("mlx_init");
		return (1);
	}
	mlx->img = create_mlx_image(mlx->mlx, RESOLUTION_X, RESOLUTION_X);
	fill_image(mlx, create_trgb(255, 65, 105, 225));
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
	mlx_hook(mlx->win, 17, 1L << 0, on_win_close, mlx);
	mlx_key_hook(mlx->win, deal_key, mlx);
	mlx_loop_hook(mlx->mlx, looper_mlx, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

t_data	create_mlx_image(void *mlx, int width, int height)
{
	t_data	img;

	img.img = mlx_new_image(mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	return (img);
}

static int	deal_key(int key, void *param)
{
	if (key == ESC_KEY)
	{
		printf("Escape pressed, quitting program...\n");
		mlx_destroy_image(((t_mlx *)param)->mlx, ((t_mlx *)param)->img.img);
		mlx_destroy_window(((t_mlx *)param)->mlx, ((t_mlx *)param)->win);
		if (ISLINUX)
			mlx_destroy_display(((t_mlx *)param)->mlx);
		free(((t_mlx *)param)->mlx);
		exit(0);
	}
	return (0);
}

static int	on_win_close(int code, void *param)
{
	printf("Quitting program...\n");
	exit(0);
	(void)param;
	(void)code;
	return (0);
}

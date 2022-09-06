/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:04:14 by davifah           #+#    #+#             */
/*   Updated: 2022/09/06 14:20:18 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "render.h"

static int	on_win_close(void *param);
static int	deal_key(int key, void *param);

int	mlx_setup(t_parse *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
	{
		perror("mlx_init");
		return (1);
	}
	data->mlx.win = mlx_new_window(data->mlx.mlx, data->render->res_width,
			data->render->res_height, "minirt");
	if (!data->mlx.win)
	{
		perror("mlx_new_window");
		return (1);
	}
	data->mlx.img = create_mlx_image(data->mlx.mlx, data->render->res_width,
			data->render->res_height);
	fill_image(&data->mlx, create_trgb(255, 65, 105, 225), data->render
		->res_width, data->render->res_height);
	mlx_put_image_to_window(
		data->mlx.mlx, data->mlx.win, data->mlx.img.img, 0, 0);
	mlx_hook(data->mlx.win, 17, 1L << 0, on_win_close, data);
	mlx_key_hook(data->mlx.win, deal_key, data);
	mlx_loop_hook(data->mlx.mlx, looper_mlx, data);
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
		on_quit_free(param);
		exit(0);
	}
	return (0);
}

static int	on_win_close(void *param)
{
	printf("Quitting program...\n");
	on_quit_free(param);
	exit(0);
	return (0);
}

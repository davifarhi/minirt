/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:44:22 by davifah           #+#    #+#             */
/*   Updated: 2022/11/09 11:16:08 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "render.h"
#include "free.h"
#include "multithreading.h"

int	print_key(int key, void *param)
{
	(void)param;
	printf("Key: %d\n", key);
	return (0);
}

void	fill_image(t_mlx *mlx, unsigned int color, int width, int height)
{
	int	i;
	int	j;

	i = -1;
	while (++i < width)
	{
		j = -1;
		while (++j < height)
			ft_pixel_put(mlx, i, j, color);
	}
}

void	ft_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	on_quit_free(t_parse *data)
{
	thread_n_function(del, 0);
	iscaplst_destroy(data->volumes);
	mlx_destroy_image(data->mlx.mlx, data->mlx.img.img);
	mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (ISLINUX)
		mlx_destroy_display(data->mlx.mlx);
	free(data->mlx.mlx);
	free_render_data(data->render);
	free_setup(data);
}

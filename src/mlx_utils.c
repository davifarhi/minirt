/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:44:22 by davifah           #+#    #+#             */
/*   Updated: 2022/08/29 12:11:51 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"

int	print_key(int key, void *param)
{
	(void)param;
	printf("Key: %d\n", key);
	return (0);
}

void	fill_image(t_mlx *mlx, unsigned int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < RESOLUTION_X)
	{
		j = -1;
		while (++j < RESOLUTION_Y)
			ft_pixel_put(mlx, i, j, color);
	}
}

void	ft_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char	*dst;

	dst = mlx->img.addr + (y * mlx->img.line_len + x * (mlx->img.bpp / 8));
	*(unsigned int *)dst = color;
}

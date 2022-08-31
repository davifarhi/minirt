/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:11:40 by davifah           #+#    #+#             */
/*   Updated: 2022/08/31 16:05:00 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CONFIG_H
# define MLX_CONFIG_H

# include "mlx.h"
# define RESOLUTION_X 854
# define RESOLUTION_Y 480

# ifdef MACOS
#  define ISLINUX 0
#  define ESC_KEY 53

void	mlx_destroy_display(void *mlx);
# else
#  define ISLINUX 1
#  define ESC_KEY 65307
# endif

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_mlx;

int		mlx_setup(t_mlx *mlx);
int		print_key(int key, void *param);
t_data	create_mlx_image(void *mlx, int width, int height);
void	fill_image(t_mlx *mlx, unsigned int color);
void	ft_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);

#endif

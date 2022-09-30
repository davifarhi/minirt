/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:11:40 by davifah           #+#    #+#             */
/*   Updated: 2022/09/06 14:22:38 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CONFIG_H
# define MLX_CONFIG_H

# include "mlx.h"
# include "minirt.h"

# ifdef MACOS
#  define ISLINUX 0
#  define ESC_KEY 53

void	mlx_destroy_display(void *mlx);
# else
#  define ISLINUX 1
#  define ESC_KEY 65307
# endif

int		mlx_setup(t_parse *data);
int		print_key(int key, void *param);
t_data	create_mlx_image(void *mlx, int width, int height);
void	fill_image(t_mlx *mlx, unsigned int color, int width, int height);
void	ft_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
void	on_quit_free(t_parse *data);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:22:00 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"
# define LINE_BY_LINE_RENDER 1

int			looper_mlx(void *param);
t_vector	render_get_camera_direction(
				t_vector *v, int x, int y);

//render_setup
double		*get_angle_shift_per_pixel(
				unsigned char fov, int width, int height);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:48:05 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define FOV 70
# define LINE_BY_LINE_RENDER 1

//resolutions of mlx window
//aspp = angle shift per pixel [x, y]
typedef struct s_render_data
{
	unsigned int	res_width;
	unsigned int	res_height;
	double			aspect_ratio;
	double			*aspp;
}	t_render_data;

int				looper_mlx(void *param);
t_vector		render_get_camera_direction(
					t_vector *v, t_render_data *render, int x, int y);

//render_setup
t_render_data	*render_setup_data(void);
void			free_render_data(t_render_data *r);

#endif

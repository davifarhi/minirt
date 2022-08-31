/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/08/31 21:11:44 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"
# define LINE_BY_LINE_RENDER 1

int			looper_mlx(void *param);
t_vector	render_get_camera_direction(t_vector *v, int x, int y);

#endif

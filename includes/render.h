/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 11:55:05 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define FOV 70
# define LINE_BY_LINE_RENDER 1

typedef struct s_quadratic_equation
{
	double	a;
	double	b;
	double	c;
}	t_quadratic_equation;

int				looper_mlx(void *param);
t_vector		render_get_camera_direction(const t_vector v,
					const t_render_data *render, int x, int y);

//render_setup
t_render_data	*render_setup_data(void);
void			free_render_data(t_render_data *r);

//render sphere test
t_obj			*create_sphere(double x, double y, double z, double radius);
int				render_sphere(const t_obj *obj,
					const t_parse *data, const t_vector *v_ray);

#endif

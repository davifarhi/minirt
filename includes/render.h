/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 18:00:01 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "minirt.h"

# define LINE_BY_LINE_RENDER	1
# define ANTIALIASING			1

typedef struct s_quadratic_equation
{
	double	a;
	double	b;
	double	c;
}	t_quadratic_equation;

typedef struct s_obj_ray_hit
{
	double		t;
	const t_obj	*obj;
}	t_obj_ray_hit;

int				looper_mlx(void *param);
t_vector		render_get_camera_direction(const t_vector v,
					const t_render_data *render, int x, int y);
void			calculate_intersection(
					const t_vector *v_ray, t_parse *data, unsigned int *color);
unsigned int	render_per_pixel(int x, int y, t_parse *data);

//render_setup
t_render_data	*render_setup_data(t_parse *setup);
void			free_render_data(t_render_data *r);

t_obj_ray_hit	*render_sphere(const t_obj *obj,
					const t_coord *ray_origin, const t_vector *v_ray);
double			plane_intersection(t_vector pl_dir, t_coord pl_origin,
					t_vector ray_dir, t_coord ray_origin);
t_obj_ray_hit	*render_plane(const t_obj *obj,
					const t_coord *ray_origin, const t_vector *v_ray);
t_obj_ray_hit	*render_cylinder(const t_obj *obj,
					const t_coord *ray_origin, const t_vector *v_ray);

// ANTIALIASING
void			render_antialiasing(
					int x, int y, const t_vector *v_ray, t_parse *data);
unsigned int	aa_color_average(unsigned int color,
					const t_render_data *render, int x, int y);

#endif

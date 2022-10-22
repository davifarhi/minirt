/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:21:15 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/22 11:03:34 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include <math.h>

static t_vector	v_rotate_x_y_copy(
		const t_vector *v_ray, double x_deg, double y_deg)
{
	t_vector	v;

	v = *v_ray;
	vector_rotate_x(&v, x_deg);
	vector_rotate_y(&v, y_deg);
	return (v);
}

unsigned int	aa_color_average(
		unsigned int color, const t_render_data *render, int x, int y)
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (!ANTIALIASING)
		return (color);
	t = (get_t(color) + get_t(render->aa_image[y * render->res_width + x])
			+ get_t(render->aa_image[y * render->res_width + x + 1])
			+ get_t(render->aa_image[(y + 1) * render->res_width + x])
			+ get_t(render->aa_image[(y + 1) * render->res_width + x + 1])) / 5;
	r = (get_r(color) + get_r(render->aa_image[y * render->res_width + x])
			+ get_r(render->aa_image[y * render->res_width + x + 1])
			+ get_r(render->aa_image[(y + 1) * render->res_width + x])
			+ get_r(render->aa_image[(y + 1) * render->res_width + x + 1])) / 5;
	g = (get_g(color) + get_g(render->aa_image[y * render->res_width + x])
			+ get_g(render->aa_image[y * render->res_width + x + 1])
			+ get_g(render->aa_image[(y + 1) * render->res_width + x])
			+ get_g(render->aa_image[(y + 1) * render->res_width + x + 1])) / 5;
	b = (get_b(color) + get_b(render->aa_image[y * render->res_width + x])
			+ get_b(render->aa_image[y * render->res_width + x + 1])
			+ get_b(render->aa_image[(y + 1) * render->res_width + x])
			+ get_b(render->aa_image[(y + 1) * render->res_width + x + 1])) / 5;
	return (create_trgb(t, r, g, b));
}

static void	render_antialiasing2(
					int x, int y, const t_vector *v_ray, t_parse *data);

//pixel 1 (top-left) create if x = 0 && y = 0
//pixel 2 (top-right) create if y = 0
//pixel 3 (bottom-left) create if x = 0
//pixel 4 (bottom-right) create always
void	render_antialiasing(int x, int y, const t_vector *v_ray, t_parse *data)
{
	t_vector	v;

	if (!ANTIALIASING)
		return ;
	if (x == 0 && y == 0)
	{
		v = v_rotate_x_y_copy(v_ray, data->render->aspp / 2,
				data->render->aspp / 2);
		calculate_intersection(&v, data,
			&data->render->aa_image[y * data->render->res_width + x]);
	}
	if (y == 0)
	{
		v = v_rotate_x_y_copy(v_ray, data->render->aspp / 2,
				-data->render->aspp / 2);
		calculate_intersection(&v, data,
			&data->render->aa_image[y * data->render->res_width + x + 1]);
	}
	render_antialiasing2(x, y, v_ray, data);
}

static void	render_antialiasing2(
		int x, int y, const t_vector *v_ray, t_parse *data)
{
	t_vector	v;

	if (x == 0)
	{
		v = v_rotate_x_y_copy(v_ray, -data->render->aspp / 2,
				data->render->aspp / 2);
		calculate_intersection(&v, data,
			&data->render->aa_image[(y + 1) * data->render->res_width + x]);
	}
	v = v_rotate_x_y_copy(v_ray, -data->render->aspp / 2,
			-data->render->aspp / 2);
	calculate_intersection(&v, data,
		&data->render->aa_image[(y + 1) * data->render->res_width + x + 1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_antialiasing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:21:15 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/22 12:00:57 by dfarhi           ###   ########.fr       */
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

static unsigned int	aa_color_average(const unsigned int colors[4])
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	t = ((unsigned int)
			get_t(colors[0]) + get_t(colors[1])
			+ get_t(colors[2]) + get_t(colors[3])) / 4;
	r = ((unsigned int)
			get_r(colors[0]) + get_r(colors[1])
			+ get_r(colors[2]) + get_r(colors[3])) / 4;
	g = ((unsigned int)
			get_g(colors[0]) + get_g(colors[1])
			+ get_g(colors[2]) + get_g(colors[3])) / 4;
	b = ((unsigned int)
			get_b(colors[0]) + get_b(colors[1])
			+ get_b(colors[2]) + get_b(colors[3])) / 4;
	return (create_trgb((int)t, (int)r, (int)g, (int)b));
}

//pixel 1 (top-left) create if x = 0 && y = 0
//pixel 2 (top-right) create if y = 0
//pixel 3 (bottom-left) create if x = 0
//pixel 4 (bottom-right) create always
unsigned int	render_antialiasing(const t_vector *v_ray, t_parse *data)
{
	t_vector		v;
	unsigned int	aa_p[4];

	aa_p[0] = 0;
	aa_p[1] = 0;
	aa_p[2] = 0;
	aa_p[3] = 0;
	v = v_rotate_x_y_copy(v_ray, data->render->aspp / 3,
			data->render->aspp / 3);
	calculate_intersection(&v, data, &aa_p[0]);
	v = v_rotate_x_y_copy(v_ray, data->render->aspp / 3,
			-data->render->aspp / 3);
	calculate_intersection(&v, data, &aa_p[1]);
	v = v_rotate_x_y_copy(v_ray, -data->render->aspp / 3,
			data->render->aspp / 3);
	calculate_intersection(&v, data, &aa_p[2]);
	v = v_rotate_x_y_copy(v_ray, -data->render->aspp / 3,
			-data->render->aspp / 3);
	calculate_intersection(&v, data, &aa_p[3]);
	return (aa_color_average(aa_p));
}

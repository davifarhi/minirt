/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:14:53 by davifah           #+#    #+#             */
/*   Updated: 2022/09/06 14:04:41 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx_config.h"
#include "minirt.h"
#include "debug.h"
#include "minirt_math.h"
#include <math.h>

static void	vector_rotate_x(t_vector *v, double x_angle)
{
	t_vector	v2;

	x_angle = calculate_degree_to_radians(x_angle);
	v2.x = v->x;
	v2.y = (v->y * cos(x_angle)) - (v->z * sin(x_angle));
	v2.z = (v->y * sin(x_angle)) + (v->z * cos(x_angle));
	*v = v2;
}

static void	vector_rotate_y(t_vector *v, double y_angle)
{
	t_vector	v2;

	y_angle = calculate_degree_to_radians(y_angle);
	v2.x = (v->x * cos(y_angle)) + (v->z * sin(y_angle));
	v2.y = v->y;
	v2.z = (-v->x * sin(y_angle)) + (v->z * cos(y_angle));
	*v = v2;
}

static void	setup_x_y_pos(
		const t_render_data *render, double *x_pos, double *y_pos)
{
	if (render->res_width % 2 != 0)
	{
		if (*x_pos > 0)
			*x_pos = ceil(*x_pos);
		else
			*x_pos = floor(*x_pos);
	}
	if (render->res_height % 2 != 0)
	{
		if (*y_pos > 0)
			*y_pos = ceil(*y_pos);
		else
			*y_pos = floor(*y_pos);
	}
}

t_vector	render_get_camera_direction(
		const t_vector v, const t_render_data *render, int x, int y)
{
	t_vector	v2;
	double		x_pos;
	double		y_pos;

	x_pos = x - (double)(render->res_width - 1) / 2.0f;
	y_pos = (render->res_height - 1 - y)
		- (double)(render->res_height - 1) / 2.0f;
	setup_x_y_pos(render, &x_pos, &y_pos);
	v2 = v;
	vector_rotate_x(&v2, x_pos * render->aspp);
	vector_rotate_y(&v2, y_pos * render->aspp);
	if (DEBUG_SHIFTED_VECTOR)
		printf("%dx%d - shifted\n(%f,%f,%f)\n", x, y, v2.x, v2.y, v2.z);
	return (v2);
}

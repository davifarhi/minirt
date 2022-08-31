/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:14:53 by davifah           #+#    #+#             */
/*   Updated: 2022/08/31 21:24:11 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx_config.h"
#include "minirt.h"
#include <math.h>

#define FOV 70

static void	vector_rotate_x(t_vector *v, double x_angle)
{
	t_vector	v2;

	v2.x = v->x;
	v2.y = (v->y * cos(x_angle)) - (v->z * sin(x_angle));
	v2.z = (v->y * sin(x_angle)) + (v->z * cos(x_angle));
	*v = v2;
}

static void	vector_rotate_y(t_vector *v, double y_angle)
{
	t_vector	v2;

	v2.x = (v->x * cos(y_angle)) + (v->z * sin(y_angle));
	v2.y = v->y;
	v2.z = (-v->x * sin(y_angle)) + (v->z * cos(y_angle));
	*v = v2;
}

t_vector	render_get_camera_direction(t_vector *v, int x, int y)
{
	double	asppx;
	double	asppy;
	double	x_pos;
	double	y_pos;

	asppx = (double)FOV / (RESOLUTION_X - 1);
	asppy = (double)FOV / (RESOLUTION_Y - 1);
	x_pos = x - (double)(RESOLUTION_X - 1) / 2.0f;
	y_pos = y - (double)(RESOLUTION_Y - 1) / 2.0f;
	if (RESOLUTION_X % 2 != 0)
	{
		if (x_pos > 0)
			x_pos = ceil(x_pos);
		else
			x_pos = floor(x_pos);
	}
	if (RESOLUTION_Y % 2 != 0)
	{
		if (y_pos > 0)
			y_pos = ceil(y_pos);
		else
			y_pos = floor(y_pos);
	}
	vector_rotate_x(v, x_pos * asppx);
	vector_rotate_y(v, y_pos * asppy);
	return (*v);
}

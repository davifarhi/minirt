/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 19:14:53 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:11:57 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "mlx_config.h"
#include "minirt.h"
#include "debug.h"
#include <math.h>

#define FOV 70

long double	calculate_degree_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

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

double	*get_angle_shift_per_pixel(unsigned char fov, int width, int height)
{
	double	*aspp;

	aspp = ft_calloc(sizeof(double), 2);
	if (width <= 1)
		width = 2;
	if (height <= 1)
		height = 2;
	aspp[0] = (double)fov / (width - 1);
	aspp[1] = (double)fov / (height - 1);
	return (aspp);
}

t_vector	render_get_camera_direction(t_vector *v, int x, int y)
{
	double	*aspp;
	double	x_pos;
	double	y_pos;

	aspp = get_angle_shift_per_pixel(FOV, RESOLUTION_X, RESOLUTION_Y);
	x_pos = x - (double)(RESOLUTION_X - 1) / 2.0f;
	y_pos = (RESOLUTION_Y - 1 - y) - (double)(RESOLUTION_Y - 1) / 2.0f;
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
	vector_rotate_x(v, x_pos * aspp[1]);
	vector_rotate_y(v, y_pos * aspp[0]);
	if (DEBUG_SHIFTED_VECTOR)
		printf("%dx%d - shifted\n(%f,%f,%f)\n", x, y, v->x, v->y, v->z);
	free(aspp);
	return (*v);
}

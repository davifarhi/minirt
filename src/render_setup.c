/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:18:39 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:44:52 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

static double	*get_angle_shift_per_pixel(
		unsigned char fov, int width, int height)
{
	double	*aspp;

	aspp = ft_calloc(sizeof(double), 2);
	if (!aspp)
		return (0);
	if (width <= 1)
		width = 2;
	if (height <= 1)
		height = 2;
	aspp[0] = (double)fov / (width - 1);
	aspp[1] = (double)fov / (height - 1);
	return (aspp);
}

t_render_data	*render_setup_data(void)
{
	t_render_data	*r;

	r = ft_calloc(sizeof(t_render_data), 1);
	if (!r)
		return (0);
	r->res_width = 854;
	r->aspect_ratio = 16 / 9;
	r->res_height = r->res_width * r->aspect_ratio;
	r->aspp = get_angle_shift_per_pixel(FOV, r->res_width, r->res_height);
	if (!r->aspp)
	{
		free(r);
		return (0);
	}
	return (r);
}

void	free_render_data(t_render_data *r)
{
	free(r->aspp);
	free(r);
}

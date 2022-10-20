/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:18:39 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 13:21:00 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

static double	get_angle_shift_per_pixel(unsigned char fov, int width)
{
	double	aspp;

	if (width <= 1)
		width = 2;
	aspp = (double)fov / (width - 1);
	return (aspp);
}

t_render_data	*render_setup_data(t_parse *setup)
{
	t_render_data	*r;

	r = ft_calloc(sizeof(t_render_data), 1);
	if (!r)
		return (0);
	r->res_width = 854;
	r->aspect_ratio = 16.0 / 9.0;
	r->res_height = r->res_width / r->aspect_ratio;
	r->aspp = get_angle_shift_per_pixel(setup->cam_fov, r->res_width);
	r->aa_image = ft_calloc(sizeof(unsigned int),
			(r->res_width + 1) * (r->res_height + 1));
	if (!r->aa_image)
		return (0);
	return (r);
}

void	free_render_data(t_render_data *r)
{
	free(r->aa_image);
	free(r);
}

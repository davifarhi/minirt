/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:18:39 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:18:53 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lights.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/05 00:12:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"

static int	ambiant_making(int obj_color, float intensity, int ambiant_color)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = (get_r(obj_color) + get_r(ambiant_color)) * intensity;
	g = (get_g(obj_color) + get_g(ambiant_color)) * intensity;
	b = (get_b(obj_color) + get_b(ambiant_color)) * intensity;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

int	render_light(t_parse *data, t_obj_ray_hit *obj_hit)
{
	int	add_ambiant;
	// int	add_light;

	add_ambiant = ambiant_making(obj_hit->obj->color,
			data->ambient_intensity, data->ambient_color);
	// add_light = fonction;
	return (add_ambiant);
}

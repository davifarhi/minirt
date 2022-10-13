/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_combinations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/13 12:31:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include <math.h>

int	additive_light(int obj_color, float intensity, int ambiant_color)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = get_r(obj_color) + get_r(ambiant_color) * intensity;
	g = get_g(obj_color) + get_g(ambiant_color) * intensity;
	b = get_b(obj_color) + get_b(ambiant_color) * intensity;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

int	mix_color(int color, float i)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = get_r(color) * i;
	g = get_g(color) * i;
	b = get_b(color) * i;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

int	multiply_light(int obj_color, float intensity, int ambiant_color)
{
	int	r;
	int	g;
	int	b;
	int	mix;

	r = ((get_r(obj_color) * get_r(ambiant_color)) / 255) * intensity;
	g = ((get_g(obj_color) * get_g(ambiant_color)) / 255) * intensity;
	b = ((get_b(obj_color) * get_b(ambiant_color)) / 255) * intensity;
	mix = create_trgb(1, r, g, b);
	return (mix);
}

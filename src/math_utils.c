/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:15:29 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 11:56:31 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "render.h"

double	calculate_degree_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	calculate_discriminant(t_quadratic_equation *abc)
{
	return (abc->b * abc->b - 4 * abc->a * abc->c);
}

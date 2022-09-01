/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:15:29 by davifah           #+#    #+#             */
/*   Updated: 2022/09/01 11:16:59 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	calculate_degree_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

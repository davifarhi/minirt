/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:16:13 by davifah           #+#    #+#             */
/*   Updated: 2022/09/07 12:05:16 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include "render.h"

double	calculate_degree_to_radians(double degrees);
double	calculate_discriminant(const t_quadratic_equation *abc);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:16:13 by davifah           #+#    #+#             */
/*   Updated: 2022/10/20 13:23:59 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MATH_H
# define MINIRT_MATH_H

# include "render.h"

double		calculate_degree_to_radians(double degrees);
double		calculate_discriminant(const t_quadratic_equation *abc);

// VECTORS
void		vector_rotate_x(t_vector *v, double x_angle);
void		vector_rotate_y(t_vector *v, double y_angle);
t_vector	v_div(const t_vector v1, double n);
t_vector	v_mult(const t_vector v1, double n);
t_vector	v_sub(const t_vector v1, const t_vector v2);
t_vector	v_add(const t_vector v1, const t_vector v2);
t_vector	v_normalize(t_vector *v);
t_vector	coord_to_vector(t_coord c);
t_vector	cross_product(const t_vector *v1, const t_vector *v2);
double		dot_product(const t_vector v1, const t_vector v2);
double		distance(const t_coord *c1, const t_coord *c2);
void		print_v(const t_vector v);

#endif

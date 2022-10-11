/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:25:17 by davifah           #+#    #+#             */
/*   Updated: 2022/10/10 12:25:40 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include <math.h>

t_vector	v_div(const t_vector v1, double n)
{
	t_vector	v;

	v.x = v1.x / n;
	v.y = v1.y / n;
	v.z = v1.z / n;
	return (v);
}

t_vector	v_mult(const t_vector v1, double n)
{
	t_vector	v;

	v.x = v1.x * n;
	v.y = v1.y * n;
	v.z = v1.z * n;
	return (v);
}

t_vector	v_sub(const t_vector v1, const t_vector v2)
{
	t_vector	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

t_vector	v_add(const t_vector v1, const t_vector v2)
{
	t_vector	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

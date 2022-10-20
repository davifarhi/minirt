/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_op3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:52:14 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/20 18:54:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_math.h"
#include <math.h>
#include "minirt.h"

t_vector	cross_product(const t_vector *v1, const t_vector *v2)
{
	t_vector	v;

	v.x = v1->y * v2->z - v1->z * v2->y;
	v.y = v1->z * v2->x - v1->x * v2->z;
	v.z = v1->x * v2->y - v1->y * v2->x;
	return (v);
}

t_vector	v_invert(const t_vector *v1)
{
	t_vector	v;

	v.x = -v1->x;
	v.y = -v1->y;
	v.z = -v1->z;
	return (v);
}

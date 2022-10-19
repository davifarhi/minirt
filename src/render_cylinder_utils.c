/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:01:14 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/18 18:01:39 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include "render.h"
#include <math.h>
#include "debug.h"

void	cy_set_is_cap(t_obj *obj, int i)
{
	if (i == 1)
		((t_cylinder *)obj->param)->is_cap = 1;
	else
		((t_cylinder *)obj->param)->is_cap = 0;
}

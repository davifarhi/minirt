/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cylinder_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 18:01:14 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 11:19:43 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "minirt_math.h"
#include "render.h"
#include <math.h>
#include "debug.h"
#include "multithreading.h"

void	cy_set_is_cap(t_obj *obj, int i)
{
	if (i == 1)
		((t_cylinder *)obj->param)->is_cap[thread_n_function(get, 0)] = 1;
	else
		((t_cylinder *)obj->param)->is_cap[thread_n_function(get, 0)] = 0;
}

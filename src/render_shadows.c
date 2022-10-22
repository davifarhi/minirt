/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/22 10:49:47 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include "lights.h"
#include <math.h>
#include <float.h>

// This function determines if the pixel is in shadow
int	is_in_shadow(t_vector light, t_coord point, t_parse *data)
{
	t_list			*tmp;
	t_obj_ray_hit	*obj_hit;
	float			t;

	tmp = data->volumes;
	v_normalize(&light);
	t = FLT_MAX;
	while (tmp)
	{
		obj_hit = 0;
		if (((t_obj *)tmp->content)->type == Sphere)
			obj_hit = render_sphere(tmp->content, &point, &light);
		else if (((t_obj *)tmp->content)->type == Plan)
			obj_hit = render_plane(tmp->content, &point, &light);
		else if (((t_obj *)tmp->content)->type == Cylinder)
			obj_hit = render_cylinder(tmp->content, &point, &light);
		if (obj_hit != 0 && obj_hit->t < t
			&& obj_hit->t < distance(&point, &data->light_coord) - 0.0001)
			t = obj_hit->t;
		tmp = tmp->next;
		free(obj_hit);
	}
	if (t < FLT_MAX)
		return (0);
	return (1);
}

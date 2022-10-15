/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/15 11:51:46 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lights.h"
#include "minirt_math.h"
#include <math.h>

t_coord	hit_point(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray)
{
	t_coord		point;

	point.x = data->cam_coord.x + (obj_hit->t * v_ray.x);
	point.y = data->cam_coord.y + (obj_hit->t * v_ray.y);
	point.z = data->cam_coord.z + (obj_hit->t * v_ray.z);
	return (point);
}

t_vector	find_normal_vector(t_parse *data,
	t_coord point, t_obj_ray_hit *obj_hit)
{
	t_vector	normal;

	(void)data;
	if (obj_hit->obj->type == Sphere)
	{
		normal.x = point.x - obj_hit->obj->coord->x;
		normal.y = point.y - obj_hit->obj->coord->y;
		normal.z = point.z - obj_hit->obj->coord->z;
	}
	else if (obj_hit->obj->type == Plan)
	{
		normal.x = point.x - ((t_vector *)obj_hit->obj->param)->x;
		normal.y = point.y - ((t_vector *)obj_hit->obj->param)->y;
		normal.z = point.z - ((t_vector *)obj_hit->obj->param)->z;
	}
	else
	{
		normal.x = 0;
		normal.y = 0;
		normal.z = 0;
	}
	return (normal);
}

float	make_light_len(t_coord point, t_coord light)
{
	float			additions;
	float			len;

	additions = pow((light.x - point.x), 2)
		+ pow((light.y - point.y), 2)
		+ pow((light.z - point.z), 2);
	len = sqrt(additions);
	return (len);
}

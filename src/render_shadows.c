/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shadows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:52:30 by davifah           #+#    #+#             */
/*   Updated: 2022/10/18 13:25:01 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "minirt_math.h"
#include "lights.h"
#include <math.h>

static t_obj_ray_hit	*render_plane_s(const t_obj *obj,
	const t_vector *v_ray, t_coord point)
{
	t_obj_ray_hit	*obj_hit;
	double			t_param;
	double			denominator;

	point.x *= -1;
	point.y *= -1;
	point.z *= -1;
	denominator = ((t_vector *)obj->param)->x * v_ray->x
		+ ((t_vector *)obj->param)->y * v_ray->y
		+ ((t_vector *)obj->param)->z * v_ray->z;
	if (denominator < 1)
		return (0);
	t_param = ((t_vector *)obj->param)->x * (obj->coord->x - point.x)
		+ ((t_vector *)obj->param)->y * (obj->coord->y - point.y)
		+ ((t_vector *)obj->param)->z * (obj->coord->z - point.z);
	t_param = t_param / denominator;
	if (t_param < 0)
		return (0);
	obj_hit = malloc(sizeof(t_obj_ray_hit));
	if (!obj_hit)
		return (0);
	obj_hit->t = t_param;
	obj_hit->obj = obj;
	return (obj_hit);
}

// This function determines if the pixel is in shadow
int	is_in_shadow(t_vector light, t_coord point, t_parse *data, t_vector normal)
{
	t_list			*tmp;
	t_obj_ray_hit	*obj_hit;
	float			t;

	tmp = data->volumes;
	v_normalize(&light);
	point.x = point.x + normal.x / 10;
	point.y = point.y + normal.y / 10;
	point.z = point.z + normal.z / 10;
	t = MAXFLOAT;
	while (tmp)
	{
		obj_hit = 0;
		if (((t_obj *)tmp->content)->type == Sphere)
			obj_hit = render_sphere(tmp->content, &point, &light);
		else if (((t_obj *)tmp->content)->type == Plan)
			obj_hit = render_plane_s(tmp->content, &light, point);
		if (obj_hit != 0 && obj_hit->t > 0 && obj_hit->t < t)
			t = obj_hit->t;
		tmp = tmp->next;
		free(obj_hit);
	}
	if (t < MAXFLOAT)
		return (0);
	return (1);
}

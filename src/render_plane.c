/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:34:01 by davifah           #+#    #+#             */
/*   Updated: 2022/09/30 16:02:39 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

t_obj_ray_hit	*render_plane(const t_obj *obj,
		const t_parse *data, const t_vector *v_ray)
{
	t_obj_ray_hit	*obj_hit;
	double			t_param;
	double			denominator;

	denominator = obj->coord->x * v_ray->x + obj->coord->y * v_ray->y
		+ obj->coord->z * v_ray->z;
	if (!denominator)
		return (0);
	t_param = ((t_vector *)obj->param)->x * (obj->coord->x - data->cam_coord.x)
		+ ((t_vector *)obj->param)->y * (obj->coord->y - data->cam_coord.y)
		+ ((t_vector *)obj->param)->z * (obj->coord->z - data->cam_coord.z);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/10/19 13:12:29 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "render.h"

# define WHITE 33554431
# define LEN 0.0000001

//render_lights
int			render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray);
int			is_in_shadow(t_vector light, t_coord point, t_parse *data);
int			additive_light(int obj_color, float intensity, int ambiant_color);
int			mix_color(int color, float i);
int			multiply_light(int obj_color, float intensity, int ambiant_color);
t_coord		hit_point(t_coord origin, t_obj_ray_hit *obj_hit, t_vector v_ray);
t_vector	find_normal_vector(t_parse *data,
				t_coord point, t_obj_ray_hit *obj_hit);
float		make_light_len(t_coord point, t_coord light);

#endif

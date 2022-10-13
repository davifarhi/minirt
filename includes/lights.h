/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/10/13 14:54:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "render.h"

//render_lights
int	render_light(t_parse *data, t_obj_ray_hit *obj_hit, t_vector v_ray);
int	is_in_shadow(t_vector light, t_coord point, t_parse *data, t_vector normal);
int	additive_light(int obj_color, float intensity, int ambiant_color);
int	mix_color(int color, float i);
int	multiply_light(int obj_color, float intensity, int ambiant_color);
#endif

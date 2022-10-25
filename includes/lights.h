/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:49 by davifah           #+#    #+#             */
/*   Updated: 2022/10/23 20:08:50 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTS_H
# define LIGHTS_H

# include "minirt.h"
# include "render.h"

# define WHITE 33554431
# define LEN 0.0001

typedef struct s_l_data
{
	t_light			light;
	t_coord			hit_point;
	t_vector		normal;
	t_vector		v_ray;
	int				previus;
	t_vector		v_light;
	int				color;
	t_obj_ray_hit	*obj_hit;
}	t_l_data;

typedef struct s_ray
{
	t_coord			origin;
	t_vector		vector;
}	t_ray;

//render_lights
int			render_light(t_parse *data,
				t_obj_ray_hit *obj_hit, t_ray ray, int color);
int			is_in_shadow(t_vector light,
				t_coord point, t_parse *data, t_coord l_coord);
int			additive_light(int obj_color, float intensity, int ambiant_color);
int			mix_color(int color, float i);
int			multiply_light(int obj_color, float intensity, int ambiant_color);
t_coord		hit_point(t_coord origin, t_obj_ray_hit *obj_hit, t_vector v_ray);
t_vector	find_normal_vector(t_coord point, t_obj_ray_hit *obj_hit);
float		make_light_len(t_coord point, t_coord light);
float		specular_light(t_l_data l, t_parse *data);
float		spot_light(t_l_data l);
int			mirror_light(t_parse *data,
				t_l_data l, int old_value, t_vector v_ray);
void		display_lights(t_light *light);

#endif

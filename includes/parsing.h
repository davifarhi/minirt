/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/10/21 17:47:34 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "expanded.h"
# include "free.h"
# include "errors.h"

// parsing general
void		setup_init(t_parse	*setup);
void		mrt_parsing(char *file, t_parse *parsed);
t_vector	split_vector(char **data, int index);
t_coord		split_coord(char **data, int index);
t_coord		*split_coord_p(char **data, int index);
t_vector	*split_vector_p(char **data, int index);
void		color_errors(char **splitted, char **rgb);
void		make_cylinder_param(char **splitted, t_obj *cylinder);
void		make_sphere_param(char **splitted, t_obj *sphere);
void		make_plan_param(char **splitted, t_obj *plan);
void		add_ambiant(char *line, t_parse *setup);
void		add_cam(char *line, t_parse *setup);
void		add_light(char *line, t_parse *setup);
void		add_lights(char *line, t_parse *setup);
void		add_volume(char *line, t_parse *setup, int type);
char		*enum_to_name(int type);
void		error_exit(char *error);

//range check
int			colors_are_in_range(char **rgb);
int			vector_is_in_range(t_vector vector);
int			light_is_in_range(double light);
int			fov_is_in_range(unsigned char fov);

// tabs utils
int			tab_len(char **tab);
void		display_tab(char **tab);

// displaying things
void		display_volumes(t_obj *volume);
void		display_setup(t_parse *setup);

#endif

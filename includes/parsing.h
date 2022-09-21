/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/21 15:58:07 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "expanded.h"

// parsing general
void		mrt_parsing(char *file, t_parse *parsed);
t_vector	split_vector(char **data, int index);
t_coord		split_coord(char **data, int index);
t_coord		*split_coord_p(char **data, int index);
t_vector	*split_vector_p(char **data, int index);
void		color_errors(char **splitted, char **rgb);
void		add_ambiant(char *line, t_parse *setup);
void		add_cam(char *line, t_parse *setup);
void		add_light(char *line, t_parse *setup);
void		add_volume(char *line, t_parse *setup, int type);
void		create_volume(char **line, t_parse *setup, t_obj *volume, int type);
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

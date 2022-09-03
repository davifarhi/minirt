/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/03 20:59:11 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "expanded.h"

// parsing general
void		mrt_parsing(char *file, t_parse *parsed);
t_vector	split_vector(char **data, int index);
t_coord		split_coord(char **data, int index);
void		color_errors(char **splitted, char **rgb);
void		add_ambiant(char *line, t_parse *setup);
void		add_cam(char *line, t_parse *setup);
void		add_light(char *line, t_parse *setup);
void		add_plan(char *line, t_parse *setup);

// tabs utils
int			tab_len(char **tab);
void		display_tab(char **tab);

// displaying things
void		display_plan(t_list *list);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/26 15:15:24 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

//free things
void	tabfree(char **tab);
void	ft_free(char *str);
void	free_volumes(t_obj *volume);
void	free_setup(t_parse *setup);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/08/30 14:15:21 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_list	*rt_parsing(char **av)
{
	t_list	*objects;
	t_obj	new;
	t_coord	coord;

	(void)av;
	coord.x = 0;
	coord.y = 0;
	coord.z = 0;
	new.type = cam;
	new.coord = coord;
	new.color = 0;
	objects = ft_lstnew(&new);
	return (objects);
}

// utiliser get_next_line pour récupérer chaque lignes. 
// gestion des erreurs
// créer la liste chainée
// 

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:44:41 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/26 17:57:07 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	tabfree(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{
		while (tab[i] != NULL)
		{
			if (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
	}
	if (tab != NULL)
	{
		free(tab);
		tab = NULL;
	}
}

void	ft_free(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
}

void	free_volumes(t_obj *volume)
{
	if (volume != NULL)
	{
		free(volume->coord);
		if (volume->type == Plan)
			free((volume->param));
		else if (volume->type == Sphere)
			free(volume->param);
		else if (volume->type == Cylinder)
		{
			free(((t_cylinder *)volume->param)->vector);
			free(volume->param);
		}
		free(volume);
	}
}

void	free_setup(t_parse *setup)
{
	ft_lstclear(&(setup->volumes), (void *)free_volumes);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 21:44:41 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/01 21:47:03 by mreymond         ###   ########.fr       */
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

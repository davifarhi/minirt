/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 15:12:49 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/01 15:15:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_name(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (ft_strnstr(&name[len - 3], ".rt", 3) && len > 3)
		return (0);
	return (1);
}

void	check_args(char**av, int ac)
{
	if (ac < 2)
	{
		printf("Too few arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (ac > 2)
	{
		printf("Too much arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (check_name(av[1]))
	{
		printf("Argument file not conform\n");
		exit(EXIT_FAILURE);
	}
}

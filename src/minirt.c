/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/08/30 18:39:22 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"

int	main(int ac, char **av)
{
	t_list	*objects;

	(void)ac;
	objects = rt_parsing(av);
	(void) objects;
	if (mlx_setup())
		return (1);
	return (0);
}

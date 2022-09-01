/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/01 15:16:01 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "parsing.h"
#include "errors.h"

int	main(int ac, char **av)
{
	t_parse	setup;
	t_mlx	mlx;

	check_args(av, ac);
	mrt_parsing(av[1], &setup);
	(void) setup;
	if (mlx_setup(&mlx))
		return (1);
	return (0);
}

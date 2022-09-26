/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/26 15:27:22 by mreymond         ###   ########.fr       */
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

	setup_init(&setup);
	check_args(av, ac);
	mrt_parsing(av[1], &setup);
	display_setup(&setup);
	free_setup(&setup);
	if (mlx_setup(&mlx))
		return (1);
	return (0);
}

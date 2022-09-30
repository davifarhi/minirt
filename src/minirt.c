/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/30 14:50:57 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "mlx_config.h"
#include "parsing.h"
#include "errors.h"
#include "debug.h"

int	main(int ac, char **av)
{
	t_parse	setup;

	setup_init(&setup);
	check_args(av, ac);
	mrt_parsing(av[1], &setup);
	if (DEBUG_PRINT_SETUP)
		display_setup(&setup);
	setup.render = render_setup_data(&setup);
	if (!setup.render || mlx_setup(&setup))
		return (1);
	mlx_loop(setup.mlx.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/26 18:06:56 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "mlx_config.h"
#include "parsing.h"
#include "errors.h"

int	main(int ac, char **av)
{
	t_parse	structure;
	t_parse	setup;
	t_list	*objects;

	setup_init(&setup);
	check_args(av, ac);
	mrt_parsing(av[1], &setup);
	display_setup(&setup);
	free_setup(&setup);
	structure.render = render_setup_data();
	if (!structure.render || mlx_setup(&structure))
		return (1);
	mlx_loop(structure.mlx.mlx);
	return (0);
}
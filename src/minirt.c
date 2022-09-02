/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/02 13:30:00 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "mlx_config.h"

int	main(int ac, char **av)
{
	t_parse	structure;
	t_list	*objects;

	(void)ac;
	objects = rt_parsing(av);
	(void) objects;
	structure.render = render_setup_data();
	if (!structure.render || mlx_setup(&structure))
		return (1);
	mlx_loop(structure.mlx.mlx);
	return (0);
}

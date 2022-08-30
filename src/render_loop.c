/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/08/30 18:32:44 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "debug.h"

int	render_loop(int code, void *param)
{
	static int	x = -1;
	static int	y = 0;

	if (++x >= RESOLUTION_X)
	{
		x = 0;
		y++;
	}
	if (y >= RESOLUTION_Y)
	{
		if (y == RESOLUTION_Y && DEBUG_LOOP_FINISHED)
		{
			ft_putstr_fd("Finished\n", 2);
			y++;
		}
		return (0);
	}
	if (DEBUG_LOOP_PIXEL)
		printf("rendering pixel x %d - y %d\n", x, y);
	(void)code;
	(void)param;
	return (0);
}

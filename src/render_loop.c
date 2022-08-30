/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifah <dfarhi@student.42lausanne.ch      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 18:12:17 by davifah           #+#    #+#             */
/*   Updated: 2022/08/30 18:25:39 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"

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
		ft_putstr_fd("finished\n", 2);
		return (0);
	}
	printf("rendering pixel x %d - y %d\n", x, y);
	(void)code;
	(void)param;
	return (0);
}

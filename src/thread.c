/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:26:42 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 16:08:21 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multithreading.h"
#include "render.h"
#include "mlx_config.h"

void	*thread_start(void *param)
{
	t_thread		*t;
	unsigned int	x;

	x = -1;
	t = param;
	thread_n_function(add, t->n);
	while (++x < t->parse->render->res_width)
	{
		if (x % 10 == 0)
		{
			pthread_mutex_lock(&t->update);
			if (t->state != alive)
			{
				t->state = dead;
				pthread_mutex_unlock(&t->update);
				return (0);
			}
			pthread_mutex_unlock(&t->update);
		}
		ft_pixel_put(&t->parse->mlx, x, t->y, render_per_pixel(x, t->y, t->parse));
	}
	pthread_mutex_lock(&t->update);
	t->state = dead;
	pthread_mutex_unlock(&t->update);
	return (NULL);
}

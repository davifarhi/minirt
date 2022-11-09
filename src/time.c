/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:03:13 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 16:32:57 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#if DBG_PRINT_RENDER_TIME == 1

static long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	render_time(void)
{
	static long long	time = 0;

	if (!time)
		time = get_time_ms();
	else if (time > 0)
	{
		printf("Render completed in %lF s\n",
			(double)(get_time_ms() - time) / 1000);
		time = -1;
	}
}

#else

void	render_time(void)
{
	return ;
}

#endif

void	ft_wait_ms(int n)
{
	long long	start;

	if (n <= 0)
		return ;
	start = get_time_ms();
	while (get_time_ms() - start < n)
		usleep(1000);
}
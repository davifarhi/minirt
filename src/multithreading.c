/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:36:40 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 15:51:05 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "multithreading.h"

void	kill_threads(t_render_data *r)
{
	unsigned int	i;
	int				is_dead;

	if (!r->threads)
		return ;
	i = -1;
	while (++i < r->thread_n)
	{
		pthread_mutex_lock(&r->threads[i].update);
		if (r->threads[i].state == alive)
			r->threads[i].state = to_die;
		pthread_mutex_unlock(&r->threads[i].update);
	}
	i = -1;
	while (++i < r->thread_n)
	{
		is_dead = 0;
		while (!is_dead)
		{
			pthread_mutex_lock(&r->threads[i].update);
			if (r->threads[i].state == dead)
				is_dead = 1;
			pthread_mutex_unlock(&r->threads[i].update);
		}
	}
}

t_thread	*create_thread_list(unsigned int n, t_parse *parse)
{
	unsigned int	i;
	t_thread		*lst;

	if (n <= 0)
		return (0);
	lst = ft_calloc(sizeof(t_thread), n);
	if (!lst)
		return (0);
	i = -1;
	while (++i < n)
	{
		lst[i].n = i;
		lst[i].parse = parse;
		lst[i].state = dead;
		pthread_mutex_init(&lst[i].update, NULL);
	}
	return (lst);
}

static int	launch_thread(
		unsigned int y, t_thread *t)
{
	t->y = y;
	t->state = alive;
	if (pthread_create(&t->tid, NULL, &thread_start, t))
		return (1);
	pthread_detach(t->tid);
	return (0);
}

int	looper_multithreaded(void *param)
{
	t_parse				*parse;
	unsigned int		i;
	static unsigned int	y = 0;

	parse = param;
	if (!y)
		render_time();
	i = -1;
	while (++i < parse->render->thread_n)
	{
		if (y >= parse->render->res_height)
		{
			render_time();
			break ;
		}
		pthread_mutex_lock(&parse->render->threads[i].update);
		if (parse->render->threads[i].state == dead
				&& launch_thread(y++, &parse->render->threads[i]))
			return (1);
		pthread_mutex_unlock(&parse->render->threads[i].update);
	}
	put_img_to_win(&parse->mlx);
	return (0);
}

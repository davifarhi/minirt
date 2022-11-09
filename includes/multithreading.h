/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:37:19 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 17:16:48 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_H
# define MULTITHREADING_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "minirt.h"

# ifndef THREAD_N
#  define THREAD_N 8
# endif

typedef enum e_thread_n
{
	get,
	add,
	create,
	del,
}	t_thread_n;

typedef enum e_state
{
	alive,
	to_die,
	dead,
}	t_state;

typedef struct s_thread
{
	unsigned int	n;
	t_parse			*parse;
	pthread_t		tid;
	pthread_mutex_t	update;
	t_state			state;
	unsigned int	y;
}	t_thread;

int			thread_n_function(t_thread_n action, unsigned int n);
int			iscaplst_create(t_list *item, int size);
void		iscaplst_destroy(t_list *item);
int			*create_mirrordepthlst(unsigned int n);
t_thread	*create_thread_list(unsigned int n, t_parse *parse);
int			looper_multithreaded(void *param);
void		*thread_start(void *param);
void		threads_wait(t_render_data *r, t_parse *parse);
void		kill_threads(t_render_data *r);
void		ft_wait_ms(int n);

#endif
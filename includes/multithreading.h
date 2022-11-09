/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:37:19 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 11:18:37 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTITHREADING_HPP
# define MULTITHREADING_HPP

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "expanded.h"

# ifndef THREAD_N
#  define THREAD_N 0
# endif

typedef enum e_thread_n
{
	get,
	add,
	create,
	del,
}	t_thread_n;

int		thread_n_function(t_thread_n action, unsigned int n);
int		iscaplst_create(t_list *item, int size);
void	iscaplst_destroy(t_list *item);

#endif

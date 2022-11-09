/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:38:27 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 11:14:02 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multithreading.h"
#include "minirt.h"

static int tid_get_n(pthread_t *lst)
{
	pthread_t 	self;
	int			i;

	self = pthread_self();
	i = -1;
	while (lst[++i])
	{
		if (lst[i] == self)
			return (i);
	}
	return (-1);
}

int	thread_n_function(t_thread_n action, unsigned int n)
{
	static pthread_t	*lst = 0;

	if (action == create && n > 0)
	{
		lst = ft_calloc(sizeof(pthread_t), n);
		if (!lst)
			return (1);
	}
	else if (action == del && lst)
	{
		free(lst);
		lst = 0;
	}
	else if (action == add && lst)
		lst[n] = pthread_self();
	else if (action == get && lst)
	{
		return (tid_get_n(lst));
	}
	return (0);
}

void	iscaplst_destroy(t_list *item)
{
	if (!item)
		return ;
	if (((t_obj *)item->content)->type == Cylinder)
		free(((t_cylinder *)((t_obj *)item->content)->param)->is_cap);
	iscaplst_destroy(item->next);
}

int	iscaplst_create(t_list *item, int size)
{
	if (!item)
		return 0;
	if (size <= 0)
		size = 1;
	if (((t_obj *)item->content)->type == Cylinder)
	{
		((t_cylinder *)((t_obj *)item->content)->param)->is_cap = ft_calloc(sizeof(char), size);
		if (!((t_cylinder *)((t_obj *)item->content)->param)->is_cap)
			return (1);
	}
	return (iscaplst_create(item->next, size));
}

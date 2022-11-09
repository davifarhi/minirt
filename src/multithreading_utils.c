/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfarhi <dfarhi@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:38:27 by dfarhi            #+#    #+#             */
/*   Updated: 2022/11/09 16:10:37 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multithreading.h"
#include "minirt.h"

int	*create_mirrordepthlst(unsigned int n)
{
	int				*lst;
	unsigned int	i;

	i = -1;
	if (!n)
		n = 1;
	lst = malloc(sizeof(int) * n);
	if (!lst)
		return (0);
	while (++i < n)
		lst[i] = DEPTH;
	return (lst);
}

static int tid_get_n(pthread_t *lst, unsigned int size)
{
	pthread_t		self;
	unsigned int	i;

	self = pthread_self();
	i = -1;
	while (++i < size)
	{
		if (lst[i] == self)
			return (i);
	}
	return (-1);
}

int	thread_n_function(t_thread_n action, unsigned int n)
{
	static pthread_t		*lst = 0;
	static unsigned int		size;

	if (action == get && lst)
		return (tid_get_n(lst, size));
	if (action == create && n > 0)
	{
		size = n;
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

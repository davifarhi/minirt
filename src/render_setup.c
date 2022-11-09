/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:18:39 by davifah           #+#    #+#             */
/*   Updated: 2022/11/09 17:33:04 by dfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "multithreading.h"

static double	get_angle_shift_per_pixel(unsigned char fov, int width)
{
	double	aspp;

	if (width <= 1)
		width = 2;
	aspp = (double)fov / (width - 1);
	return (aspp);
}

t_render_data	*render_setup_data(t_parse *setup)
{
	t_render_data	*r;

	r = ft_calloc(sizeof(t_render_data), 1);
	if (!r)
		return (0);
	r->res_width = 1500;
	r->aspect_ratio = 16.0 / 9.0;
	r->res_height = r->res_width / r->aspect_ratio;
	r->aspp = get_angle_shift_per_pixel(setup->cam_fov, r->res_width);
	r->thread_n = THREAD_N;
	if (THREAD_N < 0)
		r->thread_n = r->res_height;
	r->threads = create_thread_list(r->thread_n, setup);
	setup->mirror_depth = create_mirrordepthlst(r->thread_n);
	if ((r->thread_n && !r->threads) || !setup->mirror_depth
		|| iscaplst_create(setup->volumes, r->thread_n)
		|| thread_n_function(create, r->thread_n))
		return (0);
	return (r);
}

void	free_render_data(t_render_data *r)
{
	unsigned int	i;

	if (r->threads)
	{
		i = -1;
		while (++i < r->thread_n)
			pthread_mutex_destroy(&r->threads[i].update);
		free(r->threads);
	}
	free(r);
}

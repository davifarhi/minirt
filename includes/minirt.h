/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/08/30 13:06:05 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "expanded.h"

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_obj
{
	char		*type;
	t_coord		coord;
	t_color		color;
	void		*param;
}	t_obj;

typedef struct s_cam
{
	t_vector	orient;
	float		focal;
}	t_cam;

typedef struct s_cylinder
{
	t_vector	orient;
	float		diameter;
	float		height;
}	t_cylinder;

//colors utils
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/08/30 17:16:54 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "expanded.h"

typedef enum e_objs
{
	ambiant,
	cam,
	light,
	sphere,
	plan,
	cylinder
}	t_objs;

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

typedef struct s_obj
{
	t_objs	type;
	t_coord	coord;
	int		color;
	void	*param;
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

//parsing
t_list	*rt_parsing(char **av);

#endif

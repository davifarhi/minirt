/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:07:09 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/06 14:04:16 by davifah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "expanded.h"

typedef enum e_types
{
	ambiant,
	cam,
	light,
	sphere,
	plan,
	cylinder
}	t_types;

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
	t_types	type;
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_mlx;

//resolutions of mlx window
//aspp = angle shift per pixel [x, y]
typedef struct s_render_data
{
	unsigned int	res_width;
	unsigned int	res_height;
	double			aspect_ratio;
	double			aspp;
}	t_render_data;

typedef struct s_parse
{
	t_list			*volumes;
	unsigned char	is_there_cam;
	t_coord			cam_coord;
	t_vector		cam_v;
	unsigned char	cam_fov;
	unsigned char	is_there_amb;
	double			ambient_intensity;
	int				ambient_int;
	unsigned char	is_there_light;
	t_coord			light_coord;
	double			light_brightness;
	t_mlx			mlx;
	t_render_data	*render;
}	t_parse;

//colors utils
int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

//parsing
t_list	*rt_parsing(char **av);

#endif

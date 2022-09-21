/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:22:24 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/07 16:11:33 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

static void	display_plan(t_obj *obj)
{
	printf("––––––––––––––––––––––––––\n");
	printf("type: %s\n", enum_to_name(obj->type));
	printf("––––––––––––––––––––––––––\n");
	printf("Coordonnées:\n");
	printf("	x: %f\n", obj->coord->x);
	printf("	y: %f\n", obj->coord->y);
	printf("	z: %f\n", obj->coord->z);
	printf("Color: %d\n", obj->color);
	printf("Vector:\n");
	printf("	x: %f\n", ((t_vector *)obj->param)->x);
	printf("	y: %f\n", ((t_vector *)obj->param)->y);
	printf("	z: %f\n", ((t_vector *)obj->param)->z);
}

static void	display_sphere(t_obj *obj)
{
	printf("––––––––––––––––––––––––––\n");
	printf("type: %s\n", enum_to_name(obj->type));
	printf("––––––––––––––––––––––––––\n");
	printf("Coordonnées:\n");
	printf("	x: %f\n", obj->coord->x);
	printf("	y: %f\n", obj->coord->y);
	printf("	z: %f\n", obj->coord->z);
	printf("Color: %d\n", obj->color);
	printf("Radius: %f\n", *(double *)obj->param);
}

static void	display_cylinder(t_obj *obj)
{
	printf("––––––––––––––––––––––––––\n");
	printf("type: %s\n", enum_to_name(obj->type));
	printf("––––––––––––––––––––––––––\n");
	printf("Coordonnées:\n");
	printf("	x: %f\n", obj->coord->x);
	printf("	y: %f\n", obj->coord->y);
	printf("	z: %f\n", obj->coord->z);
	printf("Color: %d\n", obj->color);
	printf("diameter: %f\n", ((t_cylinder *)obj->param)->diameter);
	printf("height: %f\n", ((t_cylinder *)obj->param)->height);
	printf("Vector:\n");
	printf("	x: %f\n", ((t_vector *)((t_cylinder *)obj->param)->vector)->x);
	printf("	y: %f\n", ((t_vector *)((t_cylinder *)obj->param)->vector)->y);
	printf("	z: %f\n", ((t_vector *)((t_cylinder *)obj->param)->vector)->z);
}

void	display_volumes(t_obj *volume)
{
	if (volume != NULL)
	{
		if (volume->type == Plan)
			display_plan(volume);
		else if (volume->type == Sphere)
			display_sphere(volume);
		else if (volume->type == Cylinder)
			display_cylinder(volume);
	}
}

void	display_setup(t_parse *setup)
{
	if (setup->is_there_cam)
	{
		printf("Cam Coordonnées:\n	x: %f\n", setup->cam_coord.x);
		printf("	y: %f\n", setup->cam_coord.y);
		printf("	z: %f\n", setup->cam_coord.z);
		printf("Cam Vector:\n	x: %f\n", setup->cam_v.x);
		printf("	y: %f\n", setup->cam_v.y);
		printf("	z: %f\n", setup->cam_v.z);
		printf("Cam Fov: %u\n", setup->cam_fov);
	}
	if (setup->is_there_amb)
	{
		printf("Ambient intensity: %f\n", setup->ambient_intensity);
		printf("Ambient int: %d\n", setup->ambient_int);
	}
	if (setup->is_there_light)
	{
		printf("Light Coordonnées:\n	x: %f\n", setup->light_coord.x);
		printf("	y: %f\n", setup->light_coord.y);
		printf("	z: %f\n", setup->light_coord.z);
		printf("Light brightness: %f\n", setup->light_brightness);
	}
	printf("\n\n\nVOLUMES:\n");
	ft_lstiter((setup->volumes), (void *)display_volumes);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/02 16:53:39 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"

void	*display_plan(t_obj *plan)
{
	printf("type: %d\n", plan->type);
	printf("Coordonnées:\n");
	printf("	x: %f\n", plan->coord.x);
	printf("	y: %f\n", plan->coord.y);
	printf("	z: %f\n", plan->coord.z);
	printf("Color: %d\n", plan->color);
	printf("Vector:\n");
	printf("	x: %f\n", ((t_vector *)plan->param)->x);
	printf("	y: %f\n", ((t_vector *)plan->param)->y);
	printf("	z: %f\n", ((t_vector *)plan->param)->z);
	return (0);
}

void	add_plan(char *line, t_parse *setup)
{
	char		**splitted;
	char		**rgb;
	t_obj		plan;
	t_list		*new;
	t_vector	vector;

	splitted = ft_split(line, ' ');
	if (splitted != NULL && tab_len(splitted) == 4)
	{
		plan.type = Plan;
		plan.coord = split_coord(splitted, 1);
		vector = split_vector(splitted, 2);
		plan.param = &vector;
		rgb = ft_split(splitted[3], ',');
		if (rgb == NULL || tab_len(rgb) != 3)
			color_errors(splitted, rgb);
		plan.color = create_trgb(1, atoi(rgb[0]),
				atoi(rgb[1]), atoi(rgb[2]));
		tabfree(splitted);
		tabfree(rgb);
	}
	else
	{
		tabfree(splitted);
		printf("Plan parameters are not conform\n");
		exit(EXIT_FAILURE);
	}
	new = ft_lstnew(&plan);
	ft_lstadd_back(&setup->volumes, new);
	// printf("%d\n", ((t_obj *)setup->volumes->content)->type);
	ft_lstiter(setup->volumes, display_plan((t_obj *)setup->volumes->content));
}

// printf("%d\n", ((t_obj *)setup->volumes->content)->type);
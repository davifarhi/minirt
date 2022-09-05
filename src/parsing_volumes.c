/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_volumes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:32:26 by mreymond          #+#    #+#             */
/*   Updated: 2022/09/05 17:26:22 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "free.h"
#include "parsing.h"

void	display_plan(t_list *list)
{
	if (list->content != NULL)
	{
		printf("type: %d\n", ((t_obj *)list->content)->type);
		printf("Coordonnées:\n");
		printf("	x: %f\n", ((t_obj *)list->content)->coord.x);
		printf("	y: %f\n", ((t_obj *)list->content)->coord.y);
		printf("	z: %f\n", ((t_obj *)list->content)->coord.z);
		printf("Color: %d\n", ((t_obj *)list->content)->color);
		// printf("Vector:\n");
		// printf("	x: %f\n", ((t_vector *)((t_obj *)list->content)->param)->x);
		// printf("	y: %f\n", ((t_vector *)((t_obj *)list->content)->param)->y);
		// printf("	z: %f\n", ((t_vector *)((t_obj *)list->content)->param)->z);
	}
}

void	add_plan(char *line, t_parse *setup)
{
	char		**splitted;
	char		**rgb;
	t_obj		*plan;
	t_list		*new;

	splitted = ft_split(line, ' ');
	plan = malloc(sizeof(t_obj *));
	plan->param = malloc(sizeof(t_vector *));
	if (splitted != NULL && tab_len(splitted) == 4)
	{
		plan->type = Plan;
		plan->coord = split_coord(splitted, 1);
		*(t_vector *)(plan->param) = split_vector(splitted, 2);
		rgb = ft_split(splitted[3], ',');
		if (rgb == NULL || tab_len(rgb) != 3)
			color_errors(splitted, rgb);
		plan->color = create_trgb(1, atoi(rgb[0]),
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
	// (void)new;
	(void)setup;
	new = ft_lstnew(plan);
	// display_plan(new);
	if (setup->volumes->content == NULL)
	{
		setup->volumes->content = new;
		setup->volumes->next = NULL;
	}
	else
		ft_lstadd_back(&(setup->volumes), new);
		// ft_lstadd_back((t_list **)(&(setup->volumes->content)), new);
	// ft_lstiter(setup->volumes, (void *)display_plan);
	ft_lstiter(setup->volumes, (void *)display_plan);
	printf("____________________________________\n");
}

// ft_lstiter(setup->volumes, (void *)display_plan);
// printf("____________________________________\n");
// printf("%d\n", ((t_obj *)setup->volumes->content)->type);
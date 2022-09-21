/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:03:24 by dfarhi            #+#    #+#             */
/*   Updated: 2022/09/21 16:07:23 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_config.h"
#include "parsing.h"
#include "errors.h"

int	main(int ac, char **av)
{
	t_parse	setup;
	// t_mlx	mlx;

	setup_init(&setup);
	check_args(av, ac);
	mrt_parsing(av[1], &setup);
	display_setup(&setup);
	// (void) setup;
	// if (mlx_setup(&mlx))
	// 	return (1);
	return (0);
}

// 2. dans le subject il mettent des couleurs pour la lumiere meme 
// si elles ne sont pas utilises ca serait bien de ne pas donner une 
// erreur dans ce cas, aussi si on peut stocker ces valeurs ca serait 
// cool comme ca on peut decider apres si on veut faire ce bonus

// 4. free les objects qui marche avec ft_lstclear() 

// 9. aussi qu'est ce qui se passe si il y a pas de camera ou de ambient 
// light dans le fichier, on donne une erreur ou on ajoute des configurations 
// default (le subject ne defini pas, a mon avis on peut choisir)
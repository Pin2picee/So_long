/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:31:59 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:06:53 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_two(t_game *game)
{
	game->map = NULL;
	game->mlx_connection = NULL;
	game->mlx_window = NULL;
	game->img_perso = NULL;
	game->img_exit = NULL;
	game->img_collectible = NULL;
	game->img_sol = NULL;
	game->img_sol_lave = NULL;
	game->img_wall = NULL;
}

t_game	*init(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		perror("Error\n");
		return (NULL);
	}
	game->count_c = 0;
	game->count_c_check = 0;
	game->count_e = 0;
	game->count_e_check = 0;
	game->count_p = 0;
	game->count_deplacement = 0;
	game->count_c_pris = 0;
	game->last_position.x = 0;
	game->last_position.y = 0;
	init_two(game);
	return (game);
}

void	init_event(t_game *game)
{
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, ft_deplacement, game);
	mlx_hook(game->mlx_window, DestroyNotify,
		StructureNotifyMask, free_mlx, game);
}

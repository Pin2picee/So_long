/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:42:50 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:39:51 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_error(int parameter)
{
	if (parameter)
	{
		perror("Error\n");
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || tab[i] == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = init();
	if (game == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		return (1);
	}
	if (argc != 2 || !parsing(argv, game))
	{
		perror("ARG Error ----> Don't trust this ->\n");
		if (game->map)
			free_tab(game->map);
		if (game)
			free(game);
		return (1);
	}
	go_start(game);
	init_event(game);
	mlx_loop(game->mlx_connection);
	if (game->map)
		free_tab(game->map);
	if (game)
		free(game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 16:42:04 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:32:24 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fill( t_game *game, char **map_copy, t_point current)
{
	if (current.x < 0 || current.x >= game->width || current.y < 0
		|| current.y >= game->height || map_copy[current.y][current.x] == 'F'
		|| map_copy[current.y][current.x] == '1')
		return ;
	else if (map_copy[current.y][current.x] == '0'
		|| map_copy[current.y][current.x] == 'P')
		map_copy[current.y][current.x] = 'F';
	else if (map_copy[current.y][current.x] == 'C')
	{
		game->count_c_check++;
		map_copy[current.y][current.x] = 'F';
	}
	else if (map_copy[current.y][current.x] == 'E')
	{
		game->count_e_check++;
		map_copy[current.y][current.x] = 'F';
	}
	fill(game, map_copy, (t_point){current.x + 1, current.y});
	fill(game, map_copy, (t_point){current.x -1, current.y});
	fill(game, map_copy, (t_point){current.x, current.y + 1});
	fill(game, map_copy, (t_point){current.x, current.y - 1});
}

int	check_compteur(t_game *game)
{
	if (game->count_c != game->count_c_check
		|| game->count_e != game->count_e_check)
		return (0);
	return (1);
}

int	flood_fill(t_game *game)
{
	char	**copy;

	copy = copy_map(game->map, game->height);
	if (copy == NULL)
		return (0);
	fill(game, copy, game->pos_player);
	if (!check_compteur(game))
	{
		error_map_file("un collectible ou la sortie n'est pas ateignable .");
		free_tab(copy);
		return (0);
	}
	if (copy != NULL)
		free_tab(copy);
	return (1);
}

void	ft_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->pos_player.y = i;
				game->pos_player.x = j;
			}
			else if (game->map[i][j] == 'E')
			{
				game->pos_exit.y = i;
				game->pos_exit.x = j;
			}
			j++;
		}
		i++;
	}
	return ;
}

int	check_elements_two(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
				game->count_p++;
			else if (game->map[i][j] == 'C')
				game->count_c++;
			if (game->map[i][j] == 'E')
				game->count_e++;
			j++;
		}
		i++;
	}
	if (game->count_p != 1 || game->count_e != 1 || game->count_c < 1)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touche.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 20:16:49 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:19:24 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_haut(t_game *game, int x, int y)
{
	int	flag;

	flag = 0;
	if (game->map[y - 1][x] == '0' || game->map[y - 1][x] == 'C' ||
		(game->map[y - 1][x] == 'E' && check_finish_collect(game)))
	{
		if (game->map[y - 1][x] == 'C')
			flag += 1;
		if (flag == 0)
		{
			game->map[y - 1][x] = 'P';
			game->pos_player.y--;
			game->count_deplacement++;
			game->map[y][x] = '0';
		}
		if (flag == 1)
			game->map[y - 1][x] = '0';
		else if (game->count_c_pris == game->count_c)
			game->map[y][x] = 'Z';
		if (flag == 1)
			game->count_c_pris++;
		flag = 0;
	}
	return ;
}

void	ft_bas(t_game *game, int x, int y)
{
	int	flag;

	flag = 0;
	if (game->map[y + 1][x] == '0' || game->map[y + 1][x] == 'C' ||
		(game->map[y + 1][x] == 'E' && check_finish_collect(game)))
	{
		if (game->map[y + 1][x] == 'C')
			flag += 1;
		if (flag == 0)
		{
			game->map[y + 1][x] = 'P';
			game->pos_player.y++;
			game->map[y][x] = '0';
			game->count_deplacement++;
		}
		if (flag == 1)
			game->map[y + 1][x] = '0';
		else if (game->count_c_pris == game->count_c)
			game->map[y][x] = 'Z';
		if (flag == 1)
			game->count_c_pris++;
		flag = 0;
	}
	return ;
}

void	ft_gauche(t_game *game, int x, int y)
{
	int	flag;

	flag = 0;
	if (game->map[y][x - 1] == '0' || game->map[y][x - 1] == 'C' ||
		(game->map[y][x - 1] == 'E' && check_finish_collect(game)))
	{
		if (game->map[y][x - 1] == 'C')
			flag += 1;
		if (flag == 0)
		{
			game->map[y][x - 1] = 'P';
			game->pos_player.x--;
			game->map[y][x] = '0';
			game->count_deplacement++;
		}
		if (flag == 1)
			game->map[y][x - 1] = '0';
		else if (game->count_c_pris == game->count_c)
			game->map[y][x] = 'Z';
		if (flag == 1)
			game->count_c_pris++;
		flag = 0;
	}
	return ;
}

void	ft_droite(t_game *game, int x, int y)
{
	int	flag;

	flag = 0;
	if (game->map[y][x + 1] == '0' || game->map[y][x + 1] == 'C' ||
		(game->map[y][x + 1] == 'E' && check_finish_collect(game)))
	{
		if (game->map[y][x + 1] == 'C')
			flag += 1;
		if (flag == 0)
		{
			game->map[y][x + 1] = 'P';
			game->pos_player.x++;
			game->count_deplacement++;
			game->map[y][x] = '0';
		}
		if (flag == 1)
			game->map[y][x + 1] = '0';
		else if (game->count_c_pris == game->count_c)
			game->map[y][x] = 'Z';
		if (flag == 1)
			game->count_c_pris++;
		flag = 0;
	}
	return ;
}

int	ft_deplacement(int touche, t_game *game)
{
	int	x;
	int	y;

	x = game->pos_player.x;
	y = game->pos_player.y;
	if (touche == HAUT || touche == BAS || touche == GAUCHE || touche == DROITE)
	{
		if (touche == HAUT)
			ft_haut(game, x, y);
		else if (touche == BAS)
			ft_bas(game, x, y);
		else if (touche == GAUCHE)
			ft_gauche(game, x, y);
		else if (touche == DROITE)
			ft_droite(game, x, y);
		go_display_game(game);
		ft_printf("Le nombre de deplacement est egal a : %i\n",
			game->count_deplacement);
	}
	else if (touche == XK_Escape)
		free_mlx(game);
	return (0);
}

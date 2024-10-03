/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:58:36 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 19:35:20 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_mlx(t_game *game)
{
	if (game->img_perso)
		mlx_destroy_image(game->mlx_connection, game->img_perso);
	if (game->img_exit)
		mlx_destroy_image(game->mlx_connection, game->img_exit);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx_connection, game->img_collectible);
	if (game->img_sol)
		mlx_destroy_image(game->mlx_connection, game->img_sol);
	if (game->img_sol_lave)
		mlx_destroy_image(game->mlx_connection, game->img_sol_lave);
	if (game->img_wall)
		mlx_destroy_image(game->mlx_connection, game->img_wall);
	if (game->mlx_window)
		mlx_destroy_window(game->mlx_connection, game->mlx_window);
	if (game->mlx_connection)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
	free_tab(game->map);
	free(game);
	exit(0);
	return (0);
}

void	print_elements(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_wall, x * 128, y * 130);
	else if (game->map[y][x] == '0')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_sol, x * 128, y * 130);
	else if (game->map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_collectible, x * 128, y * 130);
	else if (game->map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_exit, x * 128, y * 130);
	else if (game->map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_perso, x * 128, y * 130);
	else if (game->map[y][x] == 'Z')
		mlx_put_image_to_window(game->mlx_connection,
			game->mlx_window, game->img_sol_lave, x * 128, y * 130);
}

void	go_display_game(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			print_elements(game, x, y);
			x++;
		}
		y++;
	}
	if (game->pos_player.x == game->pos_exit.x
		&& game->pos_player.y == game->pos_exit.y
		&& game->count_c_pris == game->count_c)
	{
		ft_printf("\n-------------\033[1;32m🎉🎊 You "
			"Are the winner! 🎊🎉\033[0m--------------\n");
		free_mlx(game);
		sleep(1);
	}
}

void	go_start_two(t_game *game)
{
	int	h;
	int	w;

	game->img_perso = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/perso.xpm", &w, &h);
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/collect.xpm", &w, &h);
	game->img_wall = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/mur.xpm", &w, &h);
	game->img_sol = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/sol.xpm", &w, &h);
	game->img_exit = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/exit.xpm", &w, &h);
	game->img_sol_lave = mlx_xpm_file_to_image(game->mlx_connection,
			"sprites/sol_en_lave.xpm", &w, &h);
	if (!game->img_perso || !game->img_collectible
		|| !game->img_wall || !game->img_sol
		|| !game->img_exit || !game->img_sol_lave)
	{
		free_mlx(game);
		perror("Error\n");
		return ;
	}
	else
		go_display_game(game);
}

void	go_start(t_game *game)
{
	game->mlx_connection = mlx_init();
	if (game->mlx_connection == NULL)
	{
		free_mlx(game);
		return ;
	}
	game->mlx_window = mlx_new_window(game->mlx_connection, (game->width * 128),
			(game->height * 130), "so_long");
	if (game->mlx_window == NULL)
	{
		free_mlx(game);
		return ;
	}
	go_start_two(game);
}

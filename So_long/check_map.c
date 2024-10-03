/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:49:40 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:34:31 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_square(t_game *game)
{
	int	i;

	game->width = ft_strlen(game->map[0]);
	i = 1;
	while (game->map[i] && i < game->height)
	{
		if ((unsigned int)game->width != ft_strlen(game->map[i]))
		{
			error_map_file("-----La map n'est pas rectangulaire-----");
			return (0);
		}
		i++;
	}
	if (game->height < 3)
	{
		error_map_file("-----La map est trop petite-----");
		return (0);
	}
	return (1);
}

int	check_wall_close(char **map, int height)
{
	int	i;

	i = 0;
	while (map[0][i] && map[height - 1][i])
	{
		if (map[0][i] != '1' || map[height - 1][i] != '1')
		{
			error_map_file("\n-----The Map"
				"is not close . --> haut ou bas -----\n");
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < height && map[i] && map[i][0] && map[i][ft_strlen(map[i]) - 1])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
		{
			error_map_file("\n-----The Map"
				" Is Not Close . --> droite ou gauche -----\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_elements(t_game *game)
{
	int		i;
	int		j;
	char	str[6];

	i = -1;
	ft_strlcpy(str, "01CEP", sizeof(str));
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j] != '\0')
		{
			if (!ft_strchr(str, game->map[i][j]))
			{
				error_map_file("---il y a"
					" un caratere qui n'a pas sa place !!!---");
				return (0);
			}
		}
	}
	if (!check_elements_two(game))
		return (error_map_file("\n----Il manque (un joueur, un collectible,"
				" une sortie) pour pouvoir lancer la partie, .---\n"), 0);
	ft_position(game);
	return (1);
}

int	fd_to_map(int fd, int total_lu, t_game *game)
{
	char	*str_map;
	int		lu;

	str_map = ft_calloc(sizeof(char), total_lu + 1);
	if (str_map == NULL)
	{
		error_map_file("-----Erreur d'allocation de mémoire pour str_map-----");
		return (0);
	}
	lu = read(fd, str_map, total_lu);
	if (lu != total_lu)
	{
		free(str_map);
		error_map_file("--Erreur lors de la lecture du fichier de la map--");
		return (0);
	}
	game->map = ft_split(str_map, '\n');
	free(str_map);
	if (game->map == NULL)
	{
		error_map_file("-----Erreur lors de la séparation de la map-----");
		return (0);
	}
	return (1);
}

int	check_map_put_tab(char **argv, t_game *game, int nb_lu, int total_lu)
{
	int		fd;
	char	buff_temp[1024];

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	nb_lu = read(fd, buff_temp, sizeof(buff_temp));
	while (nb_lu > 0)
	{
		total_lu += nb_lu;
		nb_lu = read(fd, buff_temp, sizeof(buff_temp));
	}
	close(fd);
	if (total_lu < 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	fd_to_map(fd, total_lu, game);
	game->height = ft_strlen_tab(game->map);
	if (!check_square(game) || !check_wall_close(game->map, game->height)
		|| !check_elements(game) || !flood_fill(game))
		return (close(fd), 0);
	close(fd);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:34:44 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:32:38 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>

# define HAUT 119
# define BAS 115
# define GAUCHE 97
# define DROITE 100
# define ECHAP 65307
# define WIN 0x00FF00

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	void	*img_perso;
	void	*img_wall;
	void	*img_sol;
	void	*img_collectible;
	void	*img_exit;
	void	*img_sol_lave;
	void	*mlx_connection;
	void	*mlx_window;
	char	**map;
	t_point	pos_exit;
	t_point	pos_player;
	t_point	last_position;
	int		height;
	int		width;
	int		count_e;
	int		count_e_check;
	int		count_c;
	int		count_c_check;
	int		count_p;
	int		count_deplacement;
	int		count_c_pris;
}			t_game;

void	check_error(int parameter);
void	error_map_file(const char *text);

t_game	*init(void);
char	**copy_map(char **map, int height);

// *** check les erreurs de la map et des extensions ***
int		parsing(char **argv, t_game *game);
int		check_square(t_game *game);
int		check_wall_close(char **map, int nb_line);
int		check_map_put_tab(char **argv, t_game *game, int nb_lu, int total_lu);
int		check_elements_two(t_game *game);
int		flood_fill(t_game *game);

// *** utils_map ***
int		ft_strlen_tab(char **str);
void	ft_position(t_game *game);
int		check_finish_collect(t_game *game);

/*---mlx---*/
void	go_start(t_game *game);
void	go_display_game(t_game *game);
int		ft_deplacement(int param, t_game *game);
void	init_event(t_game *game);
int		free_mlx(t_game *game);
void	free_tab(char **tab);

#endif
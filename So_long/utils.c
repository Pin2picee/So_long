/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:06:49 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:52:56 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_finish_collect(t_game *game)
{
	if (game->count_c_pris == game->count_c)
		return (1);
	return (0);
}

int	ft_strlen_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	i = -1;
	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
	{
		check_error(3);
		return (NULL);
	}
	while (++i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			if (copy != NULL)
				free(copy);
			return (NULL);
		}
	}
	copy[i] = NULL;
	return (copy);
}

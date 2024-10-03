/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:50:00 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:29:53 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h> // enlever

//     Mon buffer temp
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// ma structure que je vais chainer pour chaque liste

typedef struct s_listes
{
	char			*content;
	struct s_liste	*next;
}				t_listes;

// utils

void		extract_line(t_listes *stash, char **line);
void		generate_line(char **line, t_listes *stash);
t_listes	*last_maillon(t_listes *stash);
int			found_newline(t_listes *stash);
int			ft_strlen(const char *str);
void		free_stash(t_listes *stash);

// principal
char		*get_next_line(int fd);
void		buff_to_stash(t_listes **stash, char *buff, int lettre_lu);
void		read_and_stash(t_listes **stash, int fd);

void		clean_stash(t_listes **stash);

#endif

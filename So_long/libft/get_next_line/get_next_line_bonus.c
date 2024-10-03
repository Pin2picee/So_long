/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:49:43 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 21:29:26 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_listes	*stash[4096];
	char			*ligne;

	if (fd < 0 || BUFFER_SIZE <= 0
		|| read(fd, &ligne, 0) < 0 || read(fd, 0, 0) < 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	ligne = NULL;
	read_and_stash(&stash[fd], fd);
	if (stash[fd] == NULL)
		return (NULL);
	extract_line(stash[fd], &ligne);
	clean_stash(&stash[fd]);
	if (ligne[0] == '\0')
	{
		free_stash(stash[fd]);
		stash[fd] = NULL;
		free(ligne);
		return (NULL);
	}
	return (ligne);
}

// utilise read pour mallocer la taille de mon buffer et ajouter un '\0'
// puis appel une fonction qui va copier mon buffer dans le dernier
// maillon qu'on aura malloc
void	read_and_stash(t_listes **stash, int fd)
{
	char	*buff;
	int		lettre_lu;

	lettre_lu = 1;
	while (found_newline(*stash) != 1 && lettre_lu != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		lettre_lu = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stash == NULL && lettre_lu == 0) || lettre_lu == -1)
		{
			free(buff);
			return ;
		}
		buff[lettre_lu] = '\0';
		buff_to_stash(stash, buff, lettre_lu);
		free(buff);
	}
}

void	buff_to_stash(t_listes **stash, char *buff, int lettre_lu)
{
	int			i;
	t_listes	*last;
	t_listes	*new_node;

	new_node = malloc(sizeof(t_listes));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * lettre_lu + 1);
	if (new_node == NULL)
		return ;
	i = 0;
	while (buff[i] && i < lettre_lu)
	{
		new_node->content[i] = buff[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = last_maillon(*stash);
	last->next = new_node;
}

void	extract_line(t_listes *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_listes **stash)
{
	t_listes	*last;
	t_listes	*clean_node;
	int			i;
	int			j;

	clean_node = malloc(sizeof(t_listes));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = last_maillon(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(1 * (ft_strlen(last->content) - i) + 1);
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}

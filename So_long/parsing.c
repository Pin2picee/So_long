/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelmoha <abelmoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:22:30 by abelmoha          #+#    #+#             */
/*   Updated: 2024/10/03 22:07:58 by abelmoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extension(char *file)
{
	if (ft_strrchr(file, '.') == NULL)
		return (0);
	if (ft_strncmp(ft_strrchr(file, '.'), ".ber", 4)
		|| (open(file, O_RDONLY) < 0))
		return (0);
	return (1);
}

const char	*ft_message_debut(void)
{
	return ("\n❌ [ERREUR] -- Problème détecté"
		" avec le fichier de"
		" la carte!"
		"\n────────────────────────────────────────────────\n"
		"\033[1;31m   📁 Fichier : ");
}

const char	*ft_message_fin(void)
{
	return (
		"\n\033[0m   🔍 Détails : Le fichier de la carte contient"
		" des erreurs ou est inaccessible.\n"
		"   ⚠️  Vérifiez que le fichier respecte le format attendu :\n"
		"      • Les bordures doivent être composées uniquement de murs (1).\n"
		"      • Chaque ligne doit avoir la même longueur.\n"
		"      • Il doit y avoir au moins une sortie"
		" (E), un joueur (P), et un collectable (C).\n"
		"   ────────────────────────────────────────────────\n"
		"   ❗ Solution suggérée : Vérifiez ou corrigez"
		" le fichier map fourni.\n"
		"   💡 Conseil : Utilisez un éditeur de texte"
		" pour vérifier la structure de la carte.\n"
		"   ────────────────────────────────────────────────\n");
}

void	error_map_file(const char *text)
{
	ft_printf(ft_message_debut());
	ft_printf(text);
	ft_printf(ft_message_fin());
}

int	parsing(char **argv, t_game *game)
{
	if (!check_extension(argv[1]))
	{
		error_map_file(argv[1]);
		return (0);
	}
	if (!check_map_put_tab(argv, game, 0, 0))
		return (0);
	return (1);
}

/* mon parsing
	* check extension \/
	* check 
	* check la map
		-carre
		-fermer par des murs (1)
		-check si il y a bien un Pgn
*/

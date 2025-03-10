/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:19:10 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:20:54 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture_utils(t_game *game, char **content, int i, int j)
{
	if (content[i][j] == 'N' && (content[i][j + 1]
		&& content[i][j + 1] == 'O')
		&& (content[i][j + 2] && content[i][j + 2] == ' '))
		game->no = get_texture_path(content[i] + j + 3, game);
	if (content[i][j] == 'S' && (content[i][j + 1]
		&& content[i][j + 1] == 'O')
		&& (content[i][j + 2] && content[i][j + 2] == ' '))
		game->so = get_texture_path(content[i] + j + 3, game);
	if (content[i][j] == 'W' && (content[i][j + 1]
		&& content[i][j + 1] == 'E')
		&& (content[i][j + 2] && content[i][j + 2] == ' '))
		game->we = get_texture_path(content[i] + j + 3, game);
	if (content[i][j] == 'E' && (content[i][j + 1]
		&& content[i][j + 1] == 'A')
		&& (content[i][j + 2] && content[i][j + 2] == ' '))
		game->ea = get_texture_path(content[i] + j + 3, game);
}

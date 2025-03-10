/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_img.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:08:16 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:08:17 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_img_files(t_game *game)
{
	int	fd;

	fd = 0;
	fd = open(game->no, O_RDONLY);
	if (fd < 0)
		missing_img_file(game);
	fd = open(game->so, O_RDONLY);
	if (fd < 0)
		missing_img_file(game);
	fd = open(game->we, O_RDONLY);
	if (fd < 0)
		missing_img_file(game);
	fd = open(game->ea, O_RDONLY);
	if (fd < 0)
		missing_img_file(game);
}

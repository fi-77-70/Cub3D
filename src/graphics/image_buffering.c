/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_buffering.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:07:42 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:07:43 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_floor_ceiling(t_game *game)
{
	int	*data;
	int	i;

	i = -1;
	data = (int *)game->bg.addr;
	while (++i < S_WIDTH * S_HEIGHT)
	{
		if (i < S_WIDTH * (S_HEIGHT / 2))
			data[i] = game->f[0] << 16 | game->f[1] << 8 | game->f[2];
		else
			data[i] = game->c[0] << 16 | game->c[1] << 8 | game->c[2];
	}
}

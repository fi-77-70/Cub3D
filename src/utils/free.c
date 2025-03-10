/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:08:22 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:27:30 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_game *game)
{
	int	i;

	i = -1;
	if (!game->map[0])
	{
		free (game->map);
		return ;
	}
	while (game->map[++i])
		free(game->map[i]);
	free(game->map);
}

int	ft_exit(t_game *game, char **content)
{
	if (content)
		free_matrix(content);
	mlx_loop_end(game->mlx_ptr);
	if (game->ea)
		free(game->ea);
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
	if (game->map)
		free_map(game);
	mlx_destroy_image(game->mlx_ptr, game->bg.img);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
	exit (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:08:41 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:13:44 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_vector_2(t_game *game)
{
	if (game->map[(int)game->player.y][(int)game->player.x] == 'E')
	{
		game->player_dir_x = 1;
		game->player_dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 1;
	}
	if (game->map[(int)game->player.y][(int)game->player.x] == 'W')
	{
		game->player_dir_x = -1;
		game->player_dir_y = 0;
		game->plane_x = 0;
		game->plane_y = 1;
	}
}

void	init_player_vector(t_game *game)
{
	if (game->map[(int)game->player.y][(int)game->player.x] == 'N')
	{
		game->player_dir_x = 0;
		game->player_dir_y = -1;
		game->plane_x = 1;
		game->plane_y = 0;
	}
	if (game->map[(int)game->player.y][(int)game->player.x] == 'S')
	{
		game->player_dir_x = 0;
		game->player_dir_y = 1;
		game->plane_x = 1;
		game->plane_y = 0;
	}
	init_player_vector_2(game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = NULL;
	if (ac != 2)
		return (ft_printf("Error\nInvalid number of arguments\n"), 1);
	game = init();
	get_elements(game, av[1]);
	if (!check_necessary_map_components(game))
		return (printf("Error\nInvalid map\n"), ft_exit(game, NULL), 1);
	init_textures(game);
	init_player_vector(game);
	game_loop(game);
	return (0);
}

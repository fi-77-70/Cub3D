#include "cub3d.h"

void	init_game(t_game *game)
{
	//game->player_dir = NULL;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->map_start = -1;
	game->map_end = -1;
	game->map = NULL;
	game->player.x = -1;
	game->player.y = -1;
}

void	init_img(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = NULL;
	game->li.n = NULL;
	game->li.s = NULL;
	game->li.w = NULL;
	game->li.e = NULL;
}

t_game	*init(void)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (ft_printf("Error\nMalloc failed\n"), exit(1), NULL);
	init_game(game);
	init_img(game);
	return (game);
}


#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	game = NULL;
	fd = 0;
	if (ac != 2)
		return (ft_printf("Error\nInvalid number of arguments\n"), 1);
	game = init();
	get_elements(game, av[1]);
	if (check_necessary_map_components(game))
		printf("valid map\n");
	else
		printf("invalid map\n");
	//free_matrix(map);
	put_floor_ceiling(game);
	game_loop(game);
	// mlx_loop(game->mlx_ptr);
	return (0);
}

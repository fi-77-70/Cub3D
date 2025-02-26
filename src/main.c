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
	if (map_scan(game->map))
		printf("valid map\n");
	else
		printf("invalid map\n");
	//free_matrix(map);
	return (0);
}

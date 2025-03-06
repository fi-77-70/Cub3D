
#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;
	int		fd;

	game = NULL;
	fd = 0;
  (void)fd;
	if (ac != 2)
		return (ft_printf("Error\nInvalid number of arguments\n"), 1);
	game = init();
	get_elements(game, av[1]);
	if (!check_necessary_map_components(game))
		return(printf("Error\nInvalid map\n"), ft_exit(game, NULL), 1);
	init_textures(game);
	game_loop(game);
	return (0);
}

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

void	free_all(t_game *game)
{
	if (!game)
		return ;
	if (game->map)
		free_map(game);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
	free(game);
}

void	free_images(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->img[0].img);
	mlx_destroy_image(game->mlx_ptr, game->img[1].img);
	mlx_destroy_image(game->mlx_ptr, game->img[2].img);
	mlx_destroy_image(game->mlx_ptr, game->img[3].img);
}

int	ft_exit(t_game *game)
{
	free_all(game);
	exit (EXIT_SUCCESS);
}

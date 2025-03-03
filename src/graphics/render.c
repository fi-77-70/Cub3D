#include "cub3d.h"

void	get_addr(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->img[i].addr = mlx_get_data_addr(game->img[i].img,
				&game->img[i].bpp, &game->img[i].llen,
				&game->img[i].endian);
		if (!game->img[i].addr)
			close_game(game);
		i++;
	}
}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (i == NORTH)
			game->img[i].img = mlx_xpm_file_to_image(game->mlx_ptr,
					game->no, &game->img[i].width, &game->img[i].height);
		else if (i == SOUTH)
			game->img[i].img = mlx_xpm_file_to_image(game->mlx_ptr,
					game->so, &game->img[i].width, &game->img[i].height);
		else if (i == EAST)
			game->img[i].img = mlx_xpm_file_to_image(game->mlx_ptr,
					game->ea, &game->img[i].width, &game->img[i].height);
		else
			game->img[i].img = mlx_xpm_file_to_image(game->mlx_ptr,
					game->we, &game->img[i].width, &game->img[i].height);
		i++;
	}
	i = 0;
	get_addr(game);
}

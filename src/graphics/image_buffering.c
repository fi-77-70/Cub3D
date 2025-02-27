#include "cub3d.h"

void	put_floor_ceiling(t_game *game)
{
	int	*data;
	int	i;

	i = -1;
	game->bg.img = mlx_new_image(game->mlx_ptr, 800, 600);
	game->bg.addr = mlx_get_data_addr(game->bg.img, &game->bg.bpp, &game->bg.llen, &game->bg.endian);
	data = (int *)game->bg.addr;
	while (++i < 800 * 600)
	{
		if (i < 800 * 300)
			data[i] = game->f[0] << 16 | game->f[1] << 8 | game->f[2];
		else
			data[i] = game->c[0] << 16 | game->c[1] << 8 | game->c[2];
	}
}

#include "cub3d.h"

void	put_floor_ceiling(t_game *game)
{
	int	*data;
	int	i;

	i = -1;
	data = (int *)game->bg.addr;
	while (++i < 800 * 600)
	{
		if (i < 800 * 300)
			data[i] = game->f[0] << 16 | game->f[1] << 8 | game->f[2];
		else
			data[i] = game->c[0] << 16 | game->c[1] << 8 | game->c[2];
	}
}

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->map_start = -1;
	game->map_end = -1;
	game->map = NULL;
	game->player.x = -1;
	game->player.y = -1;
	game->player_dir_x = 0;
	game->player_dir_y = 0;
	game->plane_x = 1;
	game->plane_y = 0;
	game->move_forward = 0;
	game->move_back = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->rotate_left = 0;
	game->rotate_right = 0;
	game->map_height = 0;
	game->map_width = 0;
	game->player_count = 0;
}

void	init_img(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->bg.img = mlx_new_image(game->mlx_ptr, S_WIDTH, S_HEIGHT);
	game->bg.addr = mlx_get_data_addr(game->bg.img, &game->bg.bpp, &game->bg.llen, &game->bg.endian);
	game->win_ptr = mlx_new_window(game->mlx_ptr, S_WIDTH, S_HEIGHT, "cub3d");
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

void	init_ray(t_ray *ray, t_game *game)
{
	ray->camera_x = 2 * ray->x / (double)S_WIDTH - 1;
	ray->ray_dir_x = game->player_dir_x + game->plane_x * ray->camera_x;
	ray->ray_dir_y = game->player_dir_y + game->plane_y * ray->camera_x;
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->perp_wall_dist = 0;
	ray->hit = 0;
	ray->wall_x = 0;
	ray->wall_y = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->step = 0;
	ray->tex_pos = 0;
}

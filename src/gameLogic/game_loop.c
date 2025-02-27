#include "cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_line(t_game *game, t_img *frame, int x, int side, double perp_wall_dist)
{
    int		y;
    int		line_height;
    int		draw_start;
    int		draw_end;
    int		color;

	(void)game;
    // Calculate line height based on perpendicular wall distance
    line_height = (int)(600 / perp_wall_dist);
    // Calculate lowest and highest pixel to fill in current stripe
    draw_start = -line_height / 2 + 600 / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + 600 / 2;
    if (draw_end >= 600)
	{
        draw_end = 600 - 1;
	}
    // Draw the vertical line
    y = draw_start;
    while (y < draw_end)
    {
        if (side == 0)
            color = 0xFF0000; // Red color for walls hit on x-axis
        else
            color = 0x00FF00; // Green color for walls hit on y-axis
        my_mlx_pixel_put(frame, x, y, color);
        y++;
    }
}
void rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player_dir_x;
	game->player_dir_x = game->player_dir_x * cos(angle) - game->player_dir_y * sin(angle);
	game->player_dir_y = old_dir_x * sin(angle) + game->player_dir_y * cos(angle);
	old_plane_x = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = old_plane_x * sin(angle) + game->plane_y * cos(angle);
}

int	raycast(t_game *game)
{
    int		x;
    double	camera_x;
    double	ray_dir_x;
    double	ray_dir_y;
    double	side_dist_x;
    double	side_dist_y;
    double	delta_dist_x;
    double	delta_dist_y;
    double	perp_wall_dist;
    int		step_x;
    int		step_y;
    int		hit;
    int		side;
    int		map_x;
    int		map_y;

    x = 0;
    while (x < 800)
    {
        camera_x = 2 * x / 800.0 - 1;
        ray_dir_x = game->player_dir_x + game->plane_x * camera_x;
        ray_dir_y = game->player_dir_y + game->plane_y * camera_x;
        map_x = (int)game->player.x;
        map_y = (int)game->player.y;
        side_dist_x = 0;
        side_dist_y = 0;
        delta_dist_x = fabs(1 / ray_dir_x);
        delta_dist_y = fabs(1 / ray_dir_y);
        hit = 0;
        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (game->player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - game->player.x) * delta_dist_x;
        }
        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (game->player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - game->player.y) * delta_dist_y;
        }
        while (!hit)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map_x >= 0 && map_x < 37 && map_y >= 0 && map_y < 39)
            {
                if (game->map[map_y][map_x] == '1')
                {
                    hit = 1;
                }
            }
            else
            {
                hit = 1; // Stop the loop if out of bounds
            }
        }
        if (side == 0)
            perp_wall_dist = (map_x - game->player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - game->player.y + (1 - step_y) / 2) / ray_dir_y;
        // Draw the line for the current stripe
        draw_line(game, &game->bg, x, side, perp_wall_dist);
        x++;
    }
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->bg.img, 0, 0);
	return (0);
}
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

int	key_hook(int keycode, t_game *game)
{
	put_floor_ceiling(game);
	if (keycode == 65307)
		close_game(game);
	if (keycode == XK_w)
	{
		game->player.x += game->player_dir_x * 0.1;
		game->player.y += game->player_dir_y * 0.1;
	}
	if (keycode == XK_s)
	{
		game->player.x -= game->player_dir_x * 0.1;
		game->player.y -= game->player_dir_y * 0.1;
	}
	if (keycode == XK_a)
	{
		game->player.x += game->player_dir_y * 0.1;
		game->player.y -= game->player_dir_x * 0.1;
	}
	if (keycode == XK_d)
	{
		game->player.x -= game->player_dir_y * 0.1;
		game->player.y += game->player_dir_x * 0.1;
	}
	if (keycode == XK_Left)
		rotate_player(game, -0.1);
	if (keycode == XK_Right)
		rotate_player(game, 0.1);
	printf("Player position: x = %f, y = %f\n", game->player.x, game->player.y);
	printf("Player direction: x = %f, y = %f\n", game->player_dir_x, game->player_dir_y);

	return (0);
}


int	game_loop(t_game *game)
{
	put_floor_ceiling(game);
	raycast(game);
	mlx_key_hook(game->win_ptr, &key_hook, game);
	mlx_hook(game->win_ptr, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx_ptr, &raycast, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
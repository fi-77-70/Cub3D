#include "cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void draw_line(t_game *game, t_img *frame, t_ray *ray)
{
    int		y;
    int		line_height;
    int		draw_start;
    int		draw_end;
    int		color;

	(void)game;
    // Calculate line height based on perpendicular wall distance
    line_height = (int)(600 / ray->perp_wall_dist);
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
        if (ray->side == 0 && ray->ray_dir_x > 0)
            color = 0xFF0000; // Red color for walls ray->hit on x-axis
        else if (ray->side == 1 && ray->ray_dir_y < 0)
            color = 0x00FF00; // Green color for walls ray->hit on y-axis
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			color = 0x0000FF;
		else
			color = 0xFFFF00;
        my_mlx_pixel_put(frame, ray->x, y, color);
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
    t_ray	*ray;

    ray = malloc(sizeof(t_ray));
	ray->x = 0;
	game->bg.img = mlx_new_image(game->mlx_ptr, 800, 600);
	game->bg.addr = mlx_get_data_addr(game->bg.img, &game->bg.bpp, &game->bg.llen, &game->bg.endian);
	put_floor_ceiling(game);
    while (ray->x < 800)
    {
        ray->camera_x = 2 * ray->x / 800.0 - 1;
        ray->ray_dir_x = game->player_dir_x + game->plane_x * ray->camera_x;
        ray->ray_dir_y = game->player_dir_y + game->plane_y * ray->camera_x;
        ray->map_x = (int)game->player.x;
        ray->map_y = (int)game->player.y;
        ray->side_dist_x = 0;
        ray->side_dist_y = 0;
        ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
        ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
        ray->hit = 0;
        if (ray->ray_dir_x < 0)
        {
            ray->step_x = -1;
            ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
        }
        else
        {
            ray->step_x = 1;
            ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
        }
        if (ray->ray_dir_y < 0)
        {
            ray->step_y = -1;
            ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
        }
        else
        {
            ray->step_y = 1;
            ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
        }
        while (!ray->hit)
        {
            if (ray->side_dist_x < ray->side_dist_y)
            {
                ray->side_dist_x += ray->delta_dist_x;
                ray->map_x += ray->step_x;
                ray->side = 0;
            }
            else
            {
                ray->side_dist_y += ray->delta_dist_y;
                ray->map_y += ray->step_y;
                ray->side = 1;
            }
            if (ray->map_x >= 0 && ray->map_x < 37 && ray->map_y >= 0 && ray->map_y < 39)
            {
                if (game->map[ray->map_y][ray->map_x] == '1')
                {
                    ray->hit = 1;
                }
            }
            else
            {
                ray->hit = 1; // Stop the loop if out of bounds
            }
        }
        if (ray->side == 0)
            ray->perp_wall_dist = (ray->map_x - game->player.x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
        else
            ray->perp_wall_dist = (ray->map_y - game->player.y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
        // Draw the line for the current stripe
        draw_line(game, &game->bg, ray);
        ray->x += 1;
    }
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->bg.img, 0, 0);
	mlx_destroy_image(game->mlx_ptr, game->bg.img);
	return (0);
}
int	close_game(t_game *game)
{
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

int	movements(t_game *game)
{
	if (game->move_forward)
	{
		game->player.x += game->player_dir_x * 0.01;
		game->player.y += game->player_dir_y * 0.01;
	}
	if (game->move_back)
	{
		game->player.x -= game->player_dir_x * 0.01;
		game->player.y -= game->player_dir_y * 0.01;
	}
	if (game->move_left)
	{
		game->player.x += game->player_dir_y * 0.01;
		game->player.y -= game->player_dir_x * 0.01;
	}
	if (game->move_right)
	{
		game->player.x -= game->player_dir_y * 0.01;
		game->player.y += game->player_dir_x * 0.01;
	}
	if (game->rotate_left)
		rotate_player(game, -0.01);
	if (game->rotate_right)
		rotate_player(game, 0.01);
	return (0);
}

int	key_hook_press(int keycode, t_game 	*game)
{
	if (keycode == 65307)
		close_game(game);
	if (keycode == XK_w)
		game->move_forward = 1;
	if (keycode == XK_s)
		game->move_back = 1;
	if (keycode == XK_a)
		game->move_left = 1;
	if (keycode == XK_d)
		game->move_right = 1;
	if (keycode == XK_Left)
		game->rotate_left = 1;
	if (keycode == XK_Right)
		game->rotate_right = 1;
	return (0);
}

int	key_hook_release(int keycode, t_game *game)
{
	if (keycode == XK_w && game->move_forward)
		game->move_forward = 0;
	if (keycode == XK_s && game->move_back)
		game->move_back = 0;
	if (keycode == XK_a && game->move_left)
		game->move_left = 0;
	if (keycode == XK_d && game->move_right)
		game->move_right = 0;
	if (keycode == XK_Left && game->rotate_left)
		game->rotate_left = 0;
	if (keycode == XK_Right && game->rotate_right)
		game->rotate_right = 0;
	return (0);
}

int	function_caller(t_game *game)
{
	movements(game);
	raycast(game);
	return (0);
}

int	game_loop(t_game *game)
{
	// put_floor_ceiling(game);
	mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_hook(game->win_ptr, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx_ptr, &function_caller, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
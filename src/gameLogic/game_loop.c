#include "cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > S_HEIGHT - 1 || x < 0
		|| x > S_WIDTH - 1)
		return ;
	dst = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_color(t_game *game, int x, int y, int i)
{
	return (*(int *)(game->img[i].addr
		+ (y * game->img[i].llen + x * (game->img[i].bpp / 8))));
}

void draw_line(t_game *game, t_img *frame, t_ray *ray)
{
    int		line_height;
    int		draw_start;
    int		draw_end;
    int		color;

	line_height = 0;
	draw_start = 0;
	draw_end = 0;
	color = 0;
    // Calculate line height based on perpendicular wall distance
    line_height = (int)(S_HEIGHT / ray->perp_wall_dist);
	//ft_printf("line_height: %d\n", line_height);
	//ft_printf("ray->perp_wall_dist: %f\n", ray->perp_wall_dist);
    // Calculate lowest and highest pixel to fill in current stripe
    draw_start = -line_height / 2 + (S_HEIGHT / 2);
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + S_HEIGHT / 2;
	// ft_printf("draw_end: %d\n", draw_end);
	// ft_printf("draw_start: %d\n", draw_start);
    if (draw_end >= S_HEIGHT)
		draw_end = S_HEIGHT - 1;
    // Draw the vertical line
	//printf("ray->perp_wall_dist: %f\n", ray->perp_wall_dist);
	//ray->wall_x -= floor(ray->perp_wall_dist);
	//printf("ray->wall_x: %f\n", ray->wall_x);
	//ray->tex_x = (int)(ray->wall_x * 64);
	if (ray->side == 0)
		ray->wall_x = game->player.y + ray->perp_wall_dist * ray->ray_dir_y;
	else
    	ray->wall_x = game->player.x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);

	ray->tex_x = (int)(ray->wall_x * 64);
	if (ray->tex_x < 0)
   		ray->tex_x = 0;
	if (ray->tex_x >= 64)
    	ray->tex_x = 63;
	// ft_printf("ray->perp_wall_dist: %f\n", ray->perp_wall_dist);
	// ft_printf("ray->tex_x: %f\n", ray->tex_x);
	// ft_printf("ray->wall_x: %f\n", ray->wall_x);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	//printf("ray->tex_x: %f\n", ray->tex_x);
	ray->step = 1.0 * 64.0 / line_height;
	ray->tex_pos = (draw_start - (S_HEIGHT / 2) + (line_height / 2)) * ray->step;
    while (draw_start < draw_end)
    {
		ray->tex_y = ray->tex_pos;
		ray->tex_pos += ray->step;
		//printf("ray->tex_y: %f\n", ray->tex_y);
		//printf("ray->tex_pos: %f\n", ray->tex_pos);
		//printf("ray->step: %f\n", ray->step);
		/* printf("ray->tex_y: %f\n", ray->tex_y);
		printf("ray->tex_x: %f\n", ray->tex_x);
		printf("ray->tex_pos: %f\n", ray->tex_pos); */
        if (ray->side == 0 && ray->ray_dir_x > 0)
            color = get_color(game, ray->tex_x, ray->tex_y, WEST);
        else if (ray->side == 1 && ray->ray_dir_y < 0)
            color = get_color(game, ray->tex_x, ray->tex_y, SOUTH);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			color = get_color(game, ray->tex_x, ray->tex_y, EAST);
		else
			color = get_color(game, ray->tex_x, ray->tex_y, NORTH);
		// printf("color: %d\n", color);
		// printf("ray->tex_x: %f\n", ray->tex_x);
		// printf("ray->tex_y: %f\n", ray->tex_y);
		// printf("ray->step: %f\n", ray->step);
		// printf("ray->tex_pos: %f\n", ray->tex_pos);
		// printf("draw_start: %d\n", draw_start);
		// printf("draw_end: %d\n", draw_end);
		// printf("line_height: %d\n", line_height);
		// printf("ray->perp_wall_dist: %f\n", ray->perp_wall_dist);
		// printf("ray->side: %d\n", ray->side);
        my_mlx_pixel_put(frame, ray->x, draw_start, color);
        draw_start++;
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
	put_floor_ceiling(game);
    while (ray->x < S_WIDTH)
    {
        init_ray(ray, game);
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
			if (ray->side == 0)
				ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
			else
				ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
        }
        // Draw the line for the current stripe
		if (ray->side == 0)
			ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		else
			ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
/*         ft_printf("ray->perp_wall_dist: %f\n", ray->perp_wall_dist);
	    ft_printf("ray->side: %d\n", ray->side);
		ft_printf("ray->delta_dist_x: %d\n", ray->delta_dist_x);
		ft_printf("ray->side_dist_x: %d\n", ray->side_dist_x);
		ft_printf("ray->side_dist_y: %d\n", ray->side_dist_y);
		ft_printf("ray->delta_dist_y: %d\n", ray->delta_dist_y); */
	    draw_line(game, &game->bg, ray);
        ray->x += 1;
    }
	free(ray);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->bg.img, 0, 0);
	return (0);
}

int	close_game(t_game *game)
{
	mlx_loop_end(game->mlx_ptr);
    free_matrix(game->map);
	free(game->ea);
	free(game->no);
	free(game->so);
	free(game->we);
	mlx_destroy_image(game->mlx_ptr, game->img[0].img);
	mlx_destroy_image(game->mlx_ptr, game->img[1].img);
	mlx_destroy_image(game->mlx_ptr, game->img[2].img);
	mlx_destroy_image(game->mlx_ptr, game->img[3].img);
    mlx_destroy_image(game->mlx_ptr, game->bg.img);
	mlx_clear_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
    free(game);
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
	// mlx_mouse_hide(game->mlx_ptr, game->win_ptr);
	mlx_hook(game->win_ptr, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx_ptr, &function_caller, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
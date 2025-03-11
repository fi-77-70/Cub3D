/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   game_loop.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ptorrao- <ptorrao-@student.42porto.com>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/10 14:07:36 by ptorrao-		  #+#	#+#			 */
/*   Updated: 2025/03/10 14:30:38 by ptorrao-		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line_utils(t_game *game, t_ray *ray, t_p_line *p_line)
{
	p_line->line_height = (int)(S_HEIGHT / ray->perp_wall_dist);
	p_line->draw_start = -p_line->line_height / 2 + (S_HEIGHT / 2);
	if (p_line->draw_start < 0)
		p_line->draw_start = 0;
	p_line->draw_end = p_line->line_height / 2 + S_HEIGHT / 2;
	if (p_line->draw_end >= S_HEIGHT)
		p_line->draw_end = S_HEIGHT - 1;
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
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->step = 1.0 * 64.0 / p_line->line_height;
	ray->tex_pos = (p_line->draw_start - (S_HEIGHT / 2)
			+ (p_line->line_height / 2)) * ray->step;
}

void	raycast_utils(t_game *game, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y)
			* ray->delta_dist_y;
	}
}

void	raycast_utils_2(t_game *game, t_ray *ray)
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
	if (ray->map_x >= 0 && ray->map_x < game->map_width
		&& ray->map_y >= 0 && ray->map_y < game->map_height)
	{
		if (game->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	else
		ray->hit = 1;
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
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
		raycast_utils(game, ray);
		while (!ray->hit)
			raycast_utils_2(game, ray);
		if (ray->side == 0)
			ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		else
			ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
		draw_line(game, &game->bg, ray);
		ray->x += 1;
	}
	free(ray);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->bg.img, 0, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	mlx_hook(game->win_ptr, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx_ptr, &function_caller, game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, key_hook_press, game);
	mlx_hook(game->win_ptr, KeyRelease, KeyReleaseMask, key_hook_release, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

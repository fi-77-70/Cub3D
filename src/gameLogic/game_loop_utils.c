/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:29 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 15:05:46 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	key_hook_press(int keycode, t_game *game)
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

void	draw_line(t_game *game, t_img *frame, t_ray *ray)
{
	t_p_line	p_line;

	p_line = init_p_line();
	draw_line_utils(game, ray, &p_line);
	while (p_line.draw_start < p_line.draw_end)
	{
		ray->tex_y = ray->tex_pos;
		ray->tex_pos += ray->step;
		if (ray->side == 0 && ray->ray_dir_x > 0)
			p_line.color = get_color(game, ray->tex_x, ray->tex_y, WEST);
		else if (ray->side == 1 && ray->ray_dir_y < 0)
			p_line.color = get_color(game, ray->tex_x, ray->tex_y, SOUTH);
		else if (ray->side == 0 && ray->ray_dir_x < 0)
			p_line.color = get_color(game, ray->tex_x, ray->tex_y, EAST);
		else
			p_line.color = get_color(game, ray->tex_x, ray->tex_y, NORTH);
		my_mlx_pixel_put(frame, ray->x, p_line.draw_start, p_line.color);
		p_line.draw_start++;
	}
}

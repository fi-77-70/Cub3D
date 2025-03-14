/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filferna <filferna@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:07:12 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/11 10:42:28 by filferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line/get_next_line_bonus.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>
# include <stdio.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "limits.h"

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define S_WIDTH 800
# define S_HEIGHT 600

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		llen;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_p_line
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	color;
}	t_p_line;

typedef struct s_game
{
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			f[3];
	int			c[3];
	int			map_start;
	int			map_end;
	int			move_forward;
	int			move_back;
	int			move_left;
	int			move_right;
	int			rotate_left;
	int			rotate_right;
	int			map_height;
	int			map_width;
	int			player_count;
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	double		player_dir_x;
	double		player_dir_y;
	double		plane_x;
	double		plane_y;
	t_img		bg;
	t_img		frame;
	t_coord		player;
	t_img		img[4];
}	t_game;

typedef struct s_ray
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
	double	wall_x;
	double	wall_y;
	double	tex_x;
	double	tex_y;
	double	step;
	double	tex_pos;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
}	t_ray;

/* function initializes the game struct */
t_game		*init(void);

/* function initializes the img struct from minilibx wich will
be used to build the frames displayed in the game
it also initializes the window */
void		init_img(t_game *game);

/* this function initializes the textures by checking if tey
exist and can be accessed and loading them in the minilibx img struct */
void		init_textures(t_game *game);

/* function initializes the ray strcut wich will be used to calculate
the rays that will be casted in the game */
void		init_ray(t_ray *ray, t_game *game);

/* function that initializes the color, where the draw
starts and ends and the line height */
t_p_line	init_p_line(void);

/* function gets elements from the file wich declares the map and
textures and stores them in the game struct */
void		get_elements(t_game *game, char *path);

/* function validates if the map is composed only of valid charactes */
int			check_char(t_game *game);

/* function gets the path to the texture from the line */
char		*get_texture_path(char *line, t_game *game);

/* function with some utils to make get texture path work */
void		get_texture_utils(t_game *game, char **content, int i, int j);

/* this function gets the rgb values from the line and
stores them in the game struct */
int			get_rgb_values(t_game *game, char *line, bool x);

/* helper funtion to get the map from the game file */
void		get_map_utils(t_game *game, char **content, int i);

/* funtion splits the file content based on the especific content
to store it in the struct for better processing */
char		**ft_cub_split(char const *s, char c, char x);

/*function takes two strings, name (the name of the file)
and extension (the desired extension);
it then checks if the file extension the
the one given in the second parameter */
int			extension_validator(char *name, char *extension);

/* function takes the name of a file (in this case an image) and
	the desiered extension and checks if it exists and can be acessed */
int			image_validator(t_game *game, char *extension);

/*this function checks if the given array (wich represents a map)
is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int			map_scan(char **map);

/* function that raycasts based on the DDA algorithm */
int			raycast(t_game *game);

/* function that moves the player/camera based on the key pressed */
int			movements(t_game *game);

/* function that calls both movements and raycast */
int			function_caller(t_game *game);

/* function that start and continues some
action based on which key is pressed */
int			key_hook_press(int keycode, t_game *game);

/* function that stops the action executed on the function key_hook_press */
int			key_hook_release(int keycode, t_game *game);

/* function to get the color of the texture */
int			get_color(t_game *game, int x, int y, int i);
void		draw_line(t_game *game, t_img *frame, t_ray *ray);
void		rotate_player(t_game *game, double angle);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		draw_line_utils(t_game *game, t_ray *ray, t_p_line *p_line);

/* function takes an array, gets it's longest line and fills all
the other lines with spaces to match that length forming a rectangle */
char		**map_formater(char **map);

/* function splits the game frame in two and paints to colors
wich will give the illusion of floor and ceiling */
void		put_floor_ceiling(t_game *game);

/* checks if the map has all the necessary components to be valid */
int			check_necessary_map_components(t_game *game);

/* initializes the game loop functions from minilibx that make the game run */
int			game_loop(t_game *game);

/* function takes an array and returns the longest line length as an int */
int			get_arr_longest_line(char **arr);

/* funtcion frees all the alocated memory and exits the game cleanly */
int			ft_exit(t_game *game, char **content);

/* function closes the game and frees the necessary memory
if player closes the game */
int			close_game(t_game *game);

/* function dysplays an error msg if the game img files
are missing or cant be accessed */
void		missing_img_file(t_game *game);

/* function checks if the necessary files stored in the game
struct exist and can be read */
void		check_img_files(t_game *game);

/* function that exits if an image is not found */
void		missing_img_file(t_game *game);

/* function that checks if the image file exists */
void		check_img_files(t_game *game);

#endif
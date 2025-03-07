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

# define S_WIDTH 1920
# define S_HEIGHT 945

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

t_game	*init(void);

void	init_img(t_game *game);
void	init_textures(t_game *game);
void	init_ray(t_ray *ray, t_game *game);

void	get_elements(t_game *game, char *path);
int		check_char(t_game *game);

char	*get_texture_path(char *line, t_game *game);

int		get_rgb_values(t_game *game, char *line, bool x);

void	get_map_utils(t_game *game, char **content, int i);

char	**ft_cub_split(char const *s, char c, char x);

/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int		extension_validator(char *name, char *extension);

//function takes the name of a file (in this case an image) and the desiered extension and checks if it exists and can be acessed
int		image_validator(t_game *game, char *extension);

/*this function checks if the given array (wich represents a map) is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int		map_scan(char **map);

/*function takes an array, gets it's longest line and fills all the other lines with spaces to match that length forming a rectangle*/
char	**map_formater(char **map);

void	put_floor_ceiling(t_game *game);

int		check_necessary_map_components(t_game *game);

int		game_loop(t_game *game);

int		get_arr_longest_line(char **arr);

int		ft_exit(t_game *game, char **content);
int		close_game(t_game *game);

void	missing_img_file(t_game *game);

void	check_img_files(t_game *game);



#endif

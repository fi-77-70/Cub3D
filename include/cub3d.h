#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line/get_next_line_bonus.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "limits.h"

/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int		extension_validator(char *name, char *extension);
//function takes the name of a file (in this case an image) and the desiered extension and checks if it exists and can be acessed
int		image_validator(char *file, char *extension);
/*this function checks if the given array (wich represents a map) is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int		map_scan(char **map);
/*function takes an array, gets it's longest line and fills all the other lines with spaces to match that length forming a rectangle*/
char	**map_formater(char **map);

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_load_img
{
	void	*n;
	void	*s;
	void	*e;
	void	*w;
}	t_load_img;

typedef struct s_game
{
	char		player_dir;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	int			f[3];
	int			c[3];
	int			map_start;
	int			map_end;
	char		**map;
	void		*mlx_ptr;
	void		*win_ptr;
	t_coord		player;
	t_load_img	li;
}	t_game;

t_game	*init(void);
void	get_elements(t_game *game, char *path);
char	*get_texture_path(char *line);
int		get_rgb_values(t_game *game, char *line, bool x);
void	get_map_utils(t_game *game, char **content, int i);
char	**ft_cub_split(char const *s, char c, char x);

#endif

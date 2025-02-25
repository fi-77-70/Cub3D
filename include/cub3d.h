#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/libft.h"
# include "../libs/libft/get_next_line/get_next_line_bonus.h"
# include "../libs/libft/ft_printf/ft_printf.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "limits.h"

/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int	extension_validator(char *name, char *extension);
//function takes the name of a file (in this case an image) and the desiered extension and checks if it exists and can be acessed
int	image_validator(char *file, char *extension);
/*this function checks if the given array (wich represents a map) is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int	map_scan(char **map);
/*auxiliary function of the map scan function wich checks the map verticaly*/
int	map_scan_2(char ** map);


#endif

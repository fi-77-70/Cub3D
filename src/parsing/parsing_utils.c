
#include "cub3d.h"
#include <fcntl.h>
/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int	extension_validator(char *name, char *extension)
{
	int	i;
	int	j;

	if (!name || !extension || !name[0] || !extension[0])
		return (0);
	i = 0;
	j = 0;
	while (name[i])
		i++;
	while (extension[j])
		j++;
	i--;
	j--;
	while (i >= 0 && j >= 0 && name[i] && extension[j])
	{
		if (name[i] != extension[j])
			return (printf("Ivalid file extension\n"), 0);
		i--;
		j--;
		if (j == -1 && name[i] == '.')
			return (1);
	}
	return (printf("Ivalid file extension\n"), 0);
}
//function takes the name of a file (in this case an image) and the desiered extension and checks if it exists and can be acessed
int	image_validator(char *file, char *extension)
{
	if (!file || !extension || !file[0] || !extension[0])
		return (0);
	if (!extension_validator(file, extension))
		return (0);
	if (open(file, O_RDONLY) < 0)
		return (0);
	else
		return (1);
}

/*auxiliary function of the map scan function wich checks the map verticaly from the end*/
int	map_scan_4(char ** map)
{
	int	x;
	int	y;
	int	store;

	x = 0;
	y = 0;
	while (map[y])
		y++;
	y--;
	store = y;
	while (map[y][x])
	{
		while (y >= 0)
		{
			if (map[y][x] && map[y][x] == '1')
			{
				while (y >= 0 && map[y][x] != ' ')
					y--;
				if (y >= 0)
					y--;
			}
			if ((y >= 0 && map[y][x] && map[y][x] == '0') || (x - 1 >= 0 && map[y][x - 1] == '0') || (map[y][x + 1] && map[y][x + 1] == '0'))
				return (0);
			if (y >= 0)
				y--;
		}
		y = store;
		x++;
	}
	return (1);
}

/*auxiliary function of the map scan function wich checks the map horizontaly from the end*/
int	map_scan_3(char ** map)
{
	int	x;
	int	y;

	y = 0;
	x = ft_strlen(map[y]) - 1;
	while (map[y])
	{
		while (x >= 0)
		{
			if (map[y][x] && map[y][x] == '1')
			{
				while (x >= 0 && map[y][x] != ' ')
					x--;
				if (x >= 0)
				x--;
			}
			if ((x >= 0 && map[y][x] && map[y][x] == '0') || (y - 1 >= 0 && map[y - 1][x] && map[y - 1][x] == '0') || (map[y + 1] && map[y + 1][x] && map[y + 1][x] == '0'))
				return (0);
			if (x >= 0)
				x--;
		}
		y++;
		x = ft_strlen(map[y]) - 1;
	}
	return (map_scan_4(map));
}
/*auxiliary function of the map scan function wich checks the map verticaly*/
int	map_scan_2(char ** map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y][x])
	{
		while (map[y])
		{
			if (map[y][x] && map[y][x] == '1')
			{
				while (map[y] && map[y][x] && map[y][x] != ' ')
					y++;
				if (map[y])
					y++;
			}
			if ((map[y][x] && map[y][x] == '0') || (x - 1 >= 0 && map[y][x - 1] == '0') || (map[y][x + 1] && map[y][x + 1] == '0'))
				return (0);
			if (map[y])
				y++;
		}
		y = 0;
		x++;
	}
	return (map_scan_3(map));
}
/*this function checks if the given array (wich represents a map) is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int	map_scan(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] && map[y][x] == '1')
			{
				while (map[y][x] && map[y][x] != ' ')
					x++;
				if (map[y][x])
					x++;
			}
			if ((map[y][x] && map[y][x] == '0') || (y - 1 >= 0 && (map[y - 1][x] && map[y - 1][x] == '0')) || (map[y + 1] && map[y + 1][x] && map[y + 1][x] == '0'))
				return (0);
			if (map[y][x])
				x++;
		}
		x = 0;
		y++;
	}
	return (map_scan_2(map));
}


#include <fcntl.h>
/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int	extension_validator(char *name, char *extension)
{
	int	i;
	int	j;

	if (!name || !extension || !name[0] || extension[0])
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
			return (0);
		i--;
		j--;
		if (j == -1 && name[i] == '.')
			return (1);
	}
	return (0);
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
/*auxiliary function of the map scan function wich checks the map verticaly*/
int	map_scan_2(char ** map)
{
	int	x;
	int	y;
	int	check_bounds;

	x = 0;
	y = 0;
	check_bounds = 1;
	while (map[y][x])
	{
		while (map[y][x])
		{
			if (check_bounds > 0 && map[y][x] == '0')
				return (0);
			else if (map[y][x] == '1')
				check_bounds = -check_bounds;
			y++;
		}
		if (check_bounds > 0)
			return (0);
		y = 0;
		x++;
	}
	return (1);
}
/*this function checks if the given array (wich represents a map) is surrounded by walls (represented by a '1')
returns 0 if the map is not surrounded and 1 if it is */
int	map_scan(char **map)
{
	int	x;
	int	y;
	int	check_bounds;

	x = 0;
	y = 0;
	check_bounds = 1;
	while (map[y][x])
	{
		while (map[y][x])
		{
			if (check_bounds > 0 && map[y][x] == '0')
				return (0);
			else if (map[y][x] == '1')
				check_bounds = -check_bounds;
			x++;
		}
		if (check_bounds > 0)
			return (0);
		x = 0;
		y++;
	}
	return (map_scan_2(map));
}

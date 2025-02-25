
#include "cub3d.h"
#include <fcntl.h>

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

int	ft_flood(char **map, int y, int x)
{
	if ((x == 0 && map[y][x] != '1') || (y == 0 && map[y][x] != '1'))
		return (0);
	if ((x == ft_strlen(map[y] && map[y][x] != '1')) || (y == ))
}

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
			if (map[y][x] == '0')
				if(!ft_flood(map, y, x))
					return (0)
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

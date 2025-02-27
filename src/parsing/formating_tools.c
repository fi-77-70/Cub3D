#include "cub3d.h"

int	get_arr_longest_line(char **arr)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	if (!arr)
		return (0);
	while (arr[i])
	{
		while (arr[i][j])
		{
			if (j >= len)
				len = j;
			j++;
		}
		j = 0;
		i++;
	}
	return (len);
}

void	fill_spaces_in_arr(char **new_arr, char **old_arr, int len)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (old_arr[i])
	{
		while (old_arr[i][++j])
			new_arr[i][j] = old_arr[i][j];
		while (j < len)
			new_arr[i][j++] = ' ';
		new_arr[i][len] = 0;
		j = -1;
		i++;
	}
}

char	**map_formater(char **map)
{
	int		height;
	int		i;
	int		len;
	char	**new_map;

	i = 0;
	if (!map)
		return (NULL);
	len = get_arr_longest_line(map) + 1;
	height = ft_mtrlen(map);
	new_map = (char **)malloc(sizeof(char *) * (height + 1));
	while (i < height)
		new_map[i++] = (char *)malloc(sizeof(char) * (len + 1));
	new_map[height] = NULL;
	fill_spaces_in_arr(new_map, map, len);
	return (new_map);
}

int	charcter_checker_map(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != '\n' && map[y][x] != 'N'
					&& map[y][x] != 'S' && map[y][x] != 'E'
						&& map[y][x] != 'W' && map[y][x] != ' ')
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	return (1);
}

int	check_necessary_map_components(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!game->map)
		return (0);
	if (!charcter_checker_map(game->map))
		return (0);
	if (!map_scan(game->map))
		return (0);
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || game->map[y][x] == 'E'
					|| game->map[y][x] == 'W')
				return (game->player.x = x, game->player.y = y, 1);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

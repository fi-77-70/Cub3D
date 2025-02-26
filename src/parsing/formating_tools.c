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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:08:12 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:14:48 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (printf("Invalid file extension\n"), 0);
		i--;
		j--;
		if (j == -1 && name[i] == '.')
			return (1);
	}
	return (printf("Invalid file extension\n"), 0);
}

int	image_validator(t_game *game, char *extension)
{
	if (game->no && !extension_validator(game->no, extension))
		return (0);
	if (game->so && !extension_validator(game->so, extension))
		return (0);
	if (game->we && !extension_validator(game->we, extension))
		return (0);
	if (game->ea && !extension_validator(game->ea, extension))
		return (0);
	return (1);
}

int	check_flood(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
		if (map[y++][0] == 'F')
			return (0);
	while (map[0][x])
		if (map[0][x++] == 'F')
			return (0);
	x--;
	y--;
	while (x >= 0)
		if (map[y][x--] == 'F')
			return (0);
	while (y >= 0)
	{
		if (map[y][ft_strlen(map[y])] == 'F')
			return (0);
		y--;
	}
	return (1);
}

void	ft_flood(char **map, int y, int x)
{
	if (y < 0 || y >= ft_mtrlen(map) || x < 0 || x >= (int)ft_strlen(map[y]))
		return ;
	if (y < 0 || x < 0)
		return ;
	if (map[y][x] && (map[y][x] == '1' || map[y][x] == 'F'))
		return ;
	if (map[y][x] && (map[y][x] == '0' || map[y][x] == ' '))
		map[y][x] = 'F';
	ft_flood(map, y - 1, x);
	ft_flood(map, y, x + 1);
	ft_flood(map, y + 1, x);
	ft_flood(map, y, x - 1);
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
				ft_flood(map, y, x);
			x++;
		}
		x = 0;
		y++;
	}
	return (check_flood(map));
}

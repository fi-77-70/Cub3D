/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_content_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:08:30 by ptorrao-          #+#    #+#             */
/*   Updated: 2025/03/10 14:26:53 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line, t_game *game)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	path = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
		return (ft_printf("Error\nInvalid texture path\n"),
			ft_exit(game, NULL), NULL);
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '\n')
		j++;
	path = ft_substr(line, i, j);
	return (path);
}

int	get_rgb_values(t_game *game, char *line, bool x)
{
	int		i;
	char	**rgb;

	i = 0;
	rgb = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
		return (ft_printf("Error\nInvalid RGB\n"), 0);
	rgb = ft_cub_split(line + i, ',', ' ');
	if (ft_mtrlen(rgb) != 3)
		return (ft_printf("Error\nInvalid RGB\n"), 0);
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (ft_printf("Error\nInvalid RGB\n"), free_matrix(rgb), 0);
		if (x)
			game->f[i] = ft_atoi(rgb[i]);
		else
			game->c[i] = ft_atoi(rgb[i]);
		i++;
	}
	free_matrix(rgb);
	return (1);
}

void	make_map(t_game *game, char **content)
{
	int	i;
	int	j;

	i = game->map_start - 1;
	j = -1;
	game->map = (char **)malloc(sizeof(char *)
			* (game->map_end - game->map_start + 2));
	while (++i <= game->map_end)
		game->map[++j] = ft_strdup(content[i]);
	game->map[++j] = NULL;
	game->map = map_formater(game->map);
	game->map_height = ft_mtrlen(game->map);
	game->map_width = get_arr_longest_line(game->map);
	free_matrix(content);
}

void	get_map_utils(t_game *game, char **content, int i)
{
	int	j;

	j = -1;
	while (content[++i])
		;
	while (content[--i])
	{
		while (content[i][++j])
		{
			if (content[i][j] != '1' && content[i][j] != '0'
				&& content[i][j] != ' ')
				break ;
			if (content[i][j] == '1' || content[i][j] == '0')
			{
				game->map_end = i;
				break ;
			}
		}
		j = -1;
		if (game->map_end != -1)
			break ;
	}
	make_map(game, content);
}

int	check_char(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (game->map[++i])
	{
		while (game->map[i][++j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != '0'
				&& game->map[i][j] != ' ' && game->map[i][j] != 'N'
				&& game->map[i][j] != 'S' && game->map[i][j] != 'E'
				&& game->map[i][j] != 'W')
				return (ft_printf("Error\nInvalid map\n"),
					ft_exit(game, NULL), 0);
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				game->player_count++;
		}
		j = -1;
	}
	if (game->player_count != 1)
		return (ft_printf("Error\nInvalid map\n"), ft_exit(game, NULL), 0);
	return (1);
}

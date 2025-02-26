#include "cub3d.h"

char	*get_texture_path(char *line)
{
	int		i;
	char	*path;
	
	i = 0;
	path = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
		return (ft_printf("Error\nInvalid texture path\n"), NULL);
	path = ft_strdup(line + i);
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
		return (ft_printf("Error\nInvalid RGB code\n"), 0); // need free function
	rgb = ft_cub_split(line + i, ',', ' ');
	if (ft_mtrlen(rgb) != 3)
		return (ft_printf("Error\nInvalid RGB code\n"), 0); // need free function
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (ft_printf("Error\nInvalid RGB code\n"), 0);
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
	game->map = (char **)malloc(sizeof(char *) * (game->map_end - game->map_start + 2));
	while (++i <= game->map_end)
		game->map[++j] = ft_strdup(content[i]);
	game->map[++j] = NULL;
	game->map = map_formater(game->map);
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
			if (content[i][j] != '1' && content[i][j] != '0' && content[i][j] != ' ')
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

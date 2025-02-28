#include "cub3d.h"

char **get_file_content(char *path)
{
	int		fd;
	char	**content;
	int		i;

	(void)i;
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nFile not found\n");
		exit(1);
	}
	i = 0;
	content = get_arr(fd);
	close(fd);
	return (content);
}

void	get_texture(t_game *game, char **content)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (content[++i])
	{
		while (content[i][++j])
		{
			if (content[i][j] == 'N' && (content[i][j + 1] && content[i][j + 1] == 'O') && (content[i][j + 2] && content[i][j + 2] == ' '))
				game->no = get_texture_path(content[i] + j + 3);
			if (content[i][j] == 'S' && (content[i][j + 1] && content[i][j + 1] == 'O') && (content[i][j + 2] && content[i][j + 2] == ' '))
				game->so = get_texture_path(content[i] + j + 3);
			if (content[i][j] == 'W' && (content[i][j + 1] && content[i][j + 1] == 'E') && (content[i][j + 2] && content[i][j + 2] == ' '))
				game->we = get_texture_path(content[i] + j + 3);
			if (content[i][j] == 'E' && (content[i][j + 1] && content[i][j + 1] == 'A') && (content[i][j + 2] && content[i][j + 2] == ' '))
				game->ea = get_texture_path(content[i] + j + 3);
		}
		j = -1;
	}
}

void	get_rgb(t_game *game, char **content)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (content[++i])
	{
		while (content[i][++j])
		{
			if (content[i][j] == 'F' && (content[i][j + 1] && content[i][j + 1] == ' '))
				get_rgb_values(game, content[i] + j + 2, true);
			if (content[i][j] == 'C' && (content[i][j + 1] && content[i][j + 1] == ' '))
				get_rgb_values(game, content[i] + j + 2, false);
		}
		j = -1;
	}
}

void	get_map(t_game *game, char **content)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (content[++i])
	{
		while (content[i][++j])
		{
			if (content[i][j] != '1' && content[i][j] != '0' && content[i][j] != ' ')
				break ;
			if (content[i][j] == '1' || content[i][j] == '0')
			{
				game->map_start = i;
				break ;
			}
		}
		j = -1;
		if (game->map_start != -1)
			break ;
	}
	get_map_utils(game, content, i);
}

void	get_elements(t_game *game, char *path)
{
	char	**content;
	int		fd;

	(void)fd;
	fd = 0;
	if (!extension_validator(path, "cub"))
	{
		ft_printf("Error\nInvalid file extension\n");
		exit(1);
	}
	content = NULL;
	content = get_file_content(path);
	get_texture(game, content);
	get_rgb(game, content);
	get_map(game, content);
}

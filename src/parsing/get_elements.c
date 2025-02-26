#include "cub3d.h"

char **get_file_content(char *path)
{
	int		fd;
	char	**content;
	int		i;

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
				game->no = get_texture_path(content[i] + j + 2);
			if (content[i][j] == 'C' && (content[i][j + 1] && content[i][j + 1] == ' '))
				game->so = get_texture_path(content[i] + j + 2);
		}
		j = -1;
	}
}

void	get_elements(t_game *game, char *path)
{
	char	**content;

	(void)game;
	content = NULL;
	content = get_file_content(path);
	get_texture(game, content);
	//ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n\n", game->no, game->so, game->we, game->ea);
	get_rgb(game, content);
	//ft_printf("F: %d, %d, %d\nC: %d, %d, %d\n\n", game->f[0], game->f[1], game->f[2], game->c[0], game->c[1], game->c[2]);
	ft_putmtr(content);
}
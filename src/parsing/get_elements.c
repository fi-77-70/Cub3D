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

void	get_elements(t_game *game, char *path)
{
	char	**content;

	(void)game;
	content = NULL;
	content = get_file_content(path);
	ft_putmtr(content);
}
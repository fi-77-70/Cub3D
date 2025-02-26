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

int	get_rgb_values(t_game *game, char *line)
{
	int		i;
	char	**rgb;

	i = 0;
	rgb = NULL;
	while (line[i] && line[i] == ' ')
		i++;
	if (i == (int)ft_strlen(line))
		return (ft_printf("Error\nInvalid RGB code\n"), 0);
	rgb = ft_cub_split(line + i, ',', ' ');
	if (ft_mtrlen(rgb) != 3)
		return (ft_printf("Error\nInvalid RGB code\n"), 0);
	i = 0;
	while (i < 3)
	{
		if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
			return (ft_printf("Error\nInvalid RGB code\n"), 0);
		game->f[i] = ft_atoi(rgb[i]);
		ft_printf("f[%d] = %d\n", i, game->f[i]);
		i++;
	}
	free_matrix(rgb);
	return (1);
}

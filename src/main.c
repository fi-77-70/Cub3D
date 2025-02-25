#include "cub3d.h"

int	main(int ac, char **av)
{
	int		fd;
	char	**map;

	fd = 0;
	if (ac != 2)
		return (0);
	if (!extension_validator(av[1], "cub"))
		return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (printf("Error opening file: [%s]\n", av[1]), 0);
	map = get_arr(fd);
	ft_putmtr(map);
	if (map_scan(map))
		printf("valid map\n");
	else
		printf("invalid map\n");
	free_matrix(map);
	return (0);
}

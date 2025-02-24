#include "libft.h"

void	free_matrix(char **mtr)
{
	int	i;

	i = -1;
	while (mtr[++i])
		free(mtr[i]);
	free(mtr);
}

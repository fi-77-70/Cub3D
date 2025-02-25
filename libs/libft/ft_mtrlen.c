#include "libft.h"

int	ft_mtrlen(char **mtr)
{
	int	i;

	i = 0;
	if (!mtr)
		return (0);
	while (mtr[i])
		i++;
	return (i);
}

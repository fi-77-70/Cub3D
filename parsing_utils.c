
#include <fcntl.h>
/*function takes two strings, name (the name of the file) and extension (the desired extension);
it then checks if the file extension the the one given in the second parameter */
int	extension_validator(char *name, char *extension)
{
	int	i;
	int	j;

	if (!name || !extension || !name[0] || extension[0])
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
			return (0);
		i--;
		j--;
		if (j == -1 && name[i] == '.')
			return (1);
	}
	return (0);
}
//function takes the name of a file (in this case an image) and the desiered extension and checks if it exists and can be acessed
int	image_validator(char *file, char *extension)
{
	if (!file || !extension || !file[0] || !extension[0])
		return (0);
	if (!extension_validator(file, extension))
		return (0);
	if (open(file, O_RDONLY) < 0)
		return (0);
	else
		return (1);
}
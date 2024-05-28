#include <stdlib.h>
#include "pipex.h"

void	clear_cmd_array(t_cmd *arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i].args != NULL)
	{
		j = 0;
		while (arr[i].args[j] != NULL)
		{
			free(arr[i].args[j]);
			j++;
		}
		free(arr[i].args);
		if (arr[i].exec_path != NULL)
			free(arr[i].exec_path);
		i++;
	}
	return ;
}

size_t	len2d(void **arr)
{
	size_t len;
	
	if (arr == NULL)
		return (0);
	len = 0;
	while (arr[len])
		len++;
	return (len);
}

#include <stdlib.h>
#include "libft/include/ft_printf.h"
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
	free(arr);
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

void	free_2d_arr(void **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_commands(t_cmd *cmds)
{
	int i;
	int j;

	i = 0;
	while (cmds[i].args != NULL)
	{
		ft_printf("cmd: %s args: ", cmds[i].exec_path);
		j = 0;
		while (cmds[i].args[j])
		{
			ft_printf("%s ", cmds[i].args[j]);
			j++;
		}
		ft_printf("\n");


		i++;
	}
}

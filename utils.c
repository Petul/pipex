/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 10:46:34 by pleander          #+#    #+#             */
/*   Updated: 2024/06/19 10:46:59 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	free(arr);
	return ;
}

size_t	len2d(void **arr)
{
	size_t	len;

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

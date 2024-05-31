/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 08:56:31 by pleander          #+#    #+#             */
/*   Updated: 2024/05/31 10:31:15 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "pipex.h"

int **create_pipes(size_t n_pipes)
{
	size_t	i;
	int		**pipes;

	pipes = malloc(sizeof(int *) * n_pipes);
	if (!pipes)
		return (NULL);
	i = 0;

	while (i < n_pipes)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			delete_pipes(pipes, i - 1);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror(NAME);
			delete_pipes(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	delete_pipes(int **pipes, size_t n_pipes)
{
	size_t i;

	i = 0;
	while (i < n_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

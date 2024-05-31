/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/05/31 10:48:53 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "libft/include/ft_printf.h"

static int	exec_cmds(t_context *con, t_cmd *cmds, int file_fds[2], int **pipes);

int	pipex(t_context *con, t_cmd *cmds)
{
	int file_fds[2];
	int	**pipes;
	int retval;
	
	if (open_fds(file_fds, con->infile, con->outfile) < 0)
		return (1);
	pipes = create_pipes(con->n_cmds - 1);
	if (!pipes)
	{
		close_fds(file_fds);
		return (1);
	}
	retval = exec_cmds(con, cmds, file_fds, pipes);

	delete_pipes(pipes, con->n_cmds - 1);
	close_fds(file_fds);
	return (retval);
}
static int	exec_cmds(t_context *con, t_cmd *cmds, int file_fds[2], int **pipes)
{
	size_t i;
	pid_t pid;

	i = 0;
	while (i < con->n_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				dup2(file_fds[0], STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			else
				dup2(pipes[i - 1][0], STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			if (i == con->n_cmds - 1)
				dup2(file_fds[1], STDOUT);
			else
				dup2(pipes[i][1], STDOUT);
			if (execve(cmds[i].exec_path, cmds[i].args, con->envp) == -1)
			{
				perror(NAME);
				return (1);
			}
		}
		waitpid(pid, NULL, 0);
		if (i != con->n_cmds - 1)
			close(pipes[i][1]);
		i++;
	}
	return (0);
}

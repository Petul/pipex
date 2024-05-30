/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/05/30 09:17:24 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "pipex.h"

static void	exec_cmds(t_context *con, t_cmd *cmds, int file_fds[2], int **pipes);

void	pipex(t_context *con, t_cmd *cmds)
{
	int file_fds[2];
	int	**pipes;
	
	file_fds[0] = open(con->infile, O_RDONLY);
	file_fds[1] = open(con->outfile, O_WRONLY | O_CREAT);
	if (file_fds[0] < 0 || file_fds[1] < 0)
		return ;
	pipes = create_pipes(con->n_cmds - 1);
	if (!pipes)
		return ; //error
	exec_cmds(con, cmds, file_fds, pipes);
	delete_pipes(pipes, con->n_cmds - 1);
	close(file_fds[0]);
	close(file_fds[1]);
	return ;
}

static void	exec_cmds(t_context *con, t_cmd *cmds, int file_fds[2], int **pipes)
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
			execve(cmds[i].exec_path, cmds[i].args, con->envp);
			break ;
		}
		waitpid(pid, NULL, 0);
		if (i != con->n_cmds - 1)
			close(pipes[i][1]);
		i++;
	}
}

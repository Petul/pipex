/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/06/03 10:55:07 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include "pipex.h"
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"

static int	exec_cmds(t_context *con, t_cmd *cmds, int file_fds[2], int **pipes);

int	pipex(t_context *con)
{
	int		file_fds[2];
	int		**pipes;
	int		retval;
	t_cmd	*cmds;
	
	if (open_fds(file_fds, con->infile, con->outfile) < 0)
		return (1);
	cmds = parse_commands(con->args, con->n_cmds, con->path);
	if (!cmds)
	{
		close_fds(file_fds);
		return (1);
	}
	pipes = create_pipes(con->n_cmds - 1);
	if (!pipes)
	{
		clear_cmd_array(cmds);
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
	size_t	i;
	pid_t	*pids;
	int stat_loc;

	pids = ft_calloc(con->n_cmds + 1, sizeof(pid_t));
	//protect
	i = 0;
	while (i < con->n_cmds)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			if (i == 0)
			{
				if (file_fds[0] < 0)
					exit(1);
				dup2(file_fds[0], STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			}
			else
				dup2(pipes[i - 1][0], STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			if (i == con->n_cmds - 1)
			{
				if (file_fds[1] < 0)
					exit(1);
				dup2(file_fds[1], STDOUT);
			}
			else
				dup2(pipes[i][1], STDOUT);
			if (execve(cmds[i].exec_path, cmds[i].args, con->envp) == -1)
			// {
			// 	close(pipes[i][1]);
			// 	if (errno == ENOENT)
			// 	 	ft_dprintf(STDERR, "%s: %s: %s\n", NAME, "", ERR_CMD_NOT_FOUND);
			// 	else
			// 		perror(NAME);
			// }
			exit(1);
		}
		i++;
	}
	i = 0;
	// STORE PIDS TOGETHER WITH THE PROCESSES FD_S AND USED PIPES. CLOSE ASSOCIATED STUFF AT EXIT.
	pid_t pid = wait(&stat_loc);
	pid = wait(&stat_loc);
	return (0);
}

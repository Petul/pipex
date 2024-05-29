/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/05/24 15:49:17 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "libft/include/ft_printf.h"
#include "pipex.h"

void	child(t_cmd *cmd, char **envp)
{
		ft_printf("Running %s\n", cmd->exec_path);
		execve(cmd->exec_path, cmd->args, envp);
}

void	pipex(t_context *con, t_cmd *cmds)
{
	int read_fd;
	int	write_fd;
	int	fd[con->n_cmds - 1][2];
	size_t	i;
	pid_t pid;

	read_fd = open(con->infile, O_RDONLY);
	write_fd = open(con->outfile, O_WRONLY | O_CREAT);
	if (read_fd < 0 || write_fd < 0)
		return ;
	i = 0;
	while (i < con->n_cmds - 1)
	{
		if (pipe(fd[i]) == -1) //Data written on 1 can be read from 0
			return ;
		i++;
	}
	i = 0;
	while (i < con->n_cmds)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				dup2(read_fd, STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			else
				dup2(fd[i - 1][0], STDIN); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
			if (i == con->n_cmds - 1)
			{
				dup2(write_fd, STDOUT);
			}
			else
				dup2(fd[i][1], STDOUT);
			execve(cmds[i].exec_path, cmds[i].args, con->envp);
			//error if reach here
			break ;
		}
		waitpid(pid, NULL, 0);
		if (i != con->n_cmds - 1)
			close(fd[i][1]);
		i++;
	}
	close(read_fd);
	close(write_fd);
	return ;
}

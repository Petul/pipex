/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:31:13 by pleander          #+#    #+#             */
/*   Updated: 2024/06/17 16:22:54 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "libft/include/ft_printf.h"
#include "libft/include/get_next_line.h"
#include "pipex.h"

static int	child_error_return(int **pipes, t_context *con, t_children *children)
{
	delete_pipes(pipes, con->n_cmds - 1);
	free(children->child_pids);
	return (EXIT_FAILURE);
}

int	execve_error_handler(t_cmd *cmds, t_children *children)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (errno == ENOENT)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, cmds[children->n_children].exec_path, STR_CMD_NOT_FOUND);
		free(children->child_pids);
		return(CODE_CMD_NOT_FOUND);
	}
	else
		perror(NAME);
	return(EXIT_FAILURE);

}

int	spawn_child(t_fds *fds, t_context *con, t_children *children, t_cmd *cmds)
{
	if (children->n_children == 0)
	{
		if (fds->file_fds[0] < 0)
			return(child_error_return(fds->pipes, con, children));
		dup2(fds->file_fds[0], STDIN_FILENO); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
		//check dup2 failure
	}
	else
		dup2(fds->pipes[children->n_children - 1][0], STDIN_FILENO); //second argumet is the id of the duplicate file descriptor. Duplicates first argument
	if (children->n_children == con->n_cmds - 1)
	{
		if (fds->file_fds[1] < 0)
			return(child_error_return(fds->pipes, con, children));
		dup2(fds->file_fds[1], STDOUT_FILENO);
		//check dup2 failure
	}
	else
		dup2(fds->pipes[children->n_children][1], STDOUT_FILENO);
		//check dup2 failure
	delete_pipes(fds->pipes, con->n_cmds - 1);
	close_fds(fds->file_fds);
	if (execve(cmds[children->n_children].exec_path, cmds[children->n_children].args, con->envp) == -1)
		return (execve_error_handler(cmds, children));
	exit(EXIT_FAILURE);
}

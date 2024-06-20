/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:31:13 by pleander          #+#    #+#             */
/*   Updated: 2024/06/20 15:33:44 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "../libft/include/ft_printf.h"
#include "pipex_bonus.h"

static int	child_error_return(int **pipes, t_context *con,
	t_children *children)
{
	delete_pipes(pipes, con->n_cmds - 1);
	free(children->child_pids);
	return (EXIT_FAILURE);
}

static int	execve_error_handler(t_cmd *cmds, t_children *children)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (errno == ENOENT)
	{
		if (cmds[children->n_children].exec_path[0] == '.'
			|| cmds[children->n_children].exec_path[0] == '/')
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME,
				cmds[children->n_children].exec_path, strerror(errno));
		else
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME,
				cmds[children->n_children].exec_path, STR_CMD_NOT_FOUND);
		free(children->child_pids);
		return (CODE_CMD_NOT_FOUND);
	}
	else if (errno == EACCES)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME,
			cmds[children->n_children].exec_path, strerror(errno));
		free(children->child_pids);
		return (CODE_PERMISSION_DENIED);
	}
	else
		perror(NAME);
	return (EXIT_FAILURE);
}

int	spawn_child(t_fds *fds, t_context *con, t_children *children, t_cmd *cmds)
{
	if (children->n_children == 0)
	{
		if (fds->file_fds[0] < 0 || dup2(fds->file_fds[0], STDIN_FILENO) < 0)
			return (child_error_return(fds->pipes, con, children));
	}
	else
		if (dup2(fds->pipes[children->n_children - 1][0], STDIN_FILENO) < 0)
			return (child_error_return(fds->pipes, con, children));
	if (children->n_children == con->n_cmds - 1)
	{
		if (fds->file_fds[1] < 0 || dup2(fds->file_fds[1], STDOUT_FILENO) < 0)
			return (child_error_return(fds->pipes, con, children));
	}
	else
		if (dup2(fds->pipes[children->n_children][1], STDOUT_FILENO) < 0)
			return (child_error_return(fds->pipes, con, children));
	delete_pipes(fds->pipes, con->n_cmds - 1);
	close_fds(fds);
	if (execve(cmds[children->n_children].exec_path,
			cmds[children->n_children].args, con->envp) == -1)
		return (execve_error_handler(cmds, children));
	exit(EXIT_FAILURE);
}

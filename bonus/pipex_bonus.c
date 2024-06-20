/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/06/20 14:34:45 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipex_bonus.h"

static int	exec_cmds(t_context *con, t_cmd *cmds, t_fds *fds);
static int	wait_for_children(int *pid, size_t n_forks);

int	pipex(t_context *con)
{
	t_fds	fds;
	int		retval;
	t_cmd	*cmds;

	open_fds(&fds, con);
	cmds = parse_commands(con->args, con->n_cmds, con->path);
	if (!cmds)
	{
		close_fds(&fds);
		return (1);
	}
	fds.pipes = create_pipes(con->n_cmds - 1);
	if (!fds.pipes)
	{
		clear_cmd_array(cmds);
		close_fds(&fds);
		return (1);
	}
	if (con->limiter)
		read_heredoc(con->limiter, fds.heredoc_pipe[1]);
	retval = exec_cmds(con, cmds, &fds);
	close_fds(&fds);
	clear_cmd_array(cmds);
	return (retval);
}

static int	exec_cmds(t_context *con, t_cmd *cmds, t_fds *fds)
{
	t_children	children;
	int			e_status;

	children.child_pids = malloc(sizeof(pid_t) * con->n_cmds);
	if (!children.child_pids)
		return (1);
	children.n_children = 0;
	while (children.n_children < con->n_cmds)
	{
		children.child_pids[children.n_children] = fork();
		if (children.child_pids[children.n_children] == 0)
			return (spawn_child(fds, con, &children, cmds));
		if (children.child_pids[children.n_children] == -1)
		{
			children.n_children++;
			continue ;
		}
		children.n_children++;
	}
	delete_pipes(fds->pipes, con->n_cmds - 1);
	close_fds(fds);
	e_status = wait_for_children(children.child_pids, children.n_children);
	free(children.child_pids);
	return (e_status);
}

static int	wait_for_children(int *pid, size_t n_forks)
{
	int		wstatus;
	int		e_status;
	size_t	i;

	wstatus = 0;
	e_status = 0;
	i = 0;
	while (i < n_forks)
	{
		wstatus = 0;
		if (pid[i] > 0)
		{
			waitpid(pid[i], &wstatus, 0);
			if (WIFEXITED(wstatus))
				e_status = WEXITSTATUS(wstatus);
		}
		else
			e_status = EXIT_FAILURE;
		i++;
	}
	return (e_status);
}

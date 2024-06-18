/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:34 by pleander          #+#    #+#             */
/*   Updated: 2024/06/17 15:40:04 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "pipex.h"
#include "libft/include/ft_printf.h"

static int	exec_cmds(t_context *con, t_cmd *cmds, t_fds *fds);
static int	wait_for_children(int *pid, size_t n_forks);

// pid_t my_fork(void)
// {
// 	static int i = 0;
//
// 	 if (i == 1)
// 	 {
// 	 	i++;
// 	 	return (-1);
// 	 }
// 	 i++;
// 	 return (fork());
// }
//
// #define fork my_fork
//
int	pipex(t_context *con)
{
	t_fds	fds;
	int		retval;
	t_cmd	*cmds;
	
	open_fds(&fds, con);
	cmds = parse_commands(con->args, con->n_cmds, con->path);
	if (!cmds)
	{
		close_fds(fds.file_fds);
		return (1);
	}
	fds.pipes = create_pipes(con->n_cmds - 1);
	if (!fds.pipes)
	{
		clear_cmd_array(cmds);
		close_fds(fds.file_fds);
		return (1);
	}
	if (con->limiter)
		read_heredoc(con->limiter, fds.file_fds[1]); //write heredoc to write end of first pipe
	retval = exec_cmds(con, cmds, &fds);
	clear_cmd_array(cmds);
	return (retval);
}

static int	exec_cmds(t_context *con, t_cmd *cmds, t_fds *fds)
{
	t_children	children;
	int			e_status;
	
	children.child_pids = malloc(sizeof(pid_t) * con->n_cmds);
	// protect?
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
	close_fds(fds->file_fds);
	e_status = wait_for_children(children.child_pids, children.n_children);
	free(children.child_pids);
	return (e_status);
}

static int	wait_for_children(int *pid, size_t n_forks)
{
	int		wstatus = 0;
	int		e_status = 0;
	size_t	i = 0;

	while (i < n_forks)
	{
		wstatus = 0;
		if (pid[i] > 0)
		{
			waitpid(pid[i], &wstatus, 0);
			if (WIFEXITED(wstatus))
			{
				e_status = WEXITSTATUS(wstatus);
			}
		}
		else 
			e_status = EXIT_FAILURE;
		i++;
	}
	return (e_status);
}


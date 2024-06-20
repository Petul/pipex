/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:30 by pleander          #+#    #+#             */
/*   Updated: 2024/06/19 10:55:23 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "../libft/include/libft.h"

static char	**get_exec_path(char **envp);
static void	get_args(t_context *con, int argc, char **argv);
static void	get_args_heredoc(t_context *con, int argc, char **argv);

int	main(int argc, char **argv, char **envp)
{
	t_context	con;
	int			retval;

	if (argc < 5)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		get_args_heredoc(&con, argc, argv);
	else
		get_args(&con, argc, argv);
	con.envp = envp;
	con.path = get_exec_path(envp);
	if (!con.path)
		return (1);
	retval = pipex(&con);
	free_2d_arr((void **)con.path, len2d((void **)con.path));
	return (retval);
}

static void	get_args_heredoc(t_context *con, int argc, char **argv)
{
	con->infile = NULL;
	con->limiter = argv[2];
	con->outfile = argv[argc - 1];
	con->n_cmds = argc - 4;
	con->args = argv + 3;
}

static void	get_args(t_context *con, int argc, char **argv)
{
	con->limiter = NULL;
	con->infile = argv[1];
	con->outfile = argv[argc - 1];
	con->n_cmds = argc - 3;
	con->args = argv + 2;
}

static char	**get_exec_path(char **envp)
{
	char	**path;

	while (*envp != NULL && ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (*envp == NULL)
		path = ft_split("", 0);
	else
		path = ft_split((*envp) + 5, ':');
	if (!path)
		return (NULL);
	return (path);
}

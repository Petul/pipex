/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:30 by pleander          #+#    #+#             */
/*   Updated: 2024/06/03 09:59:59 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/ft_printf.h"
#include "pipex.h"
#include "libft/include/libft.h"

static char **get_exec_path(char **envp);

int	main(int argc, char **argv, char **envp)
{
	t_context con;
	int		retval;

	int i = 0;
	while (i < argc)
	{
		ft_printf("%s, ", argv[i]);
		i++;
	}
	ft_printf("\n");
	if (argc < 5)
		return (1);
	con.infile = argv[1];
	con.outfile = argv[argc - 1];
	//con.n_cmds = 2;
	con.n_cmds = argc - 3;
	con.envp = envp;
	con.args = argv + 2;
	con.path = get_exec_path(envp);
	if (!con.path)
		return (1);
	retval = pipex(&con);
	free_2d_arr((void **)con.path, len2d((void **)con.path));
	return (retval);
}

static char **get_exec_path(char **envp)
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

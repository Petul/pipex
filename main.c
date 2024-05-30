/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:30 by pleander          #+#    #+#             */
/*   Updated: 2024/05/30 09:46:57 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include "pipex.h"

char **get_exec_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) && *envp != NULL)
		envp++;
	if (*envp == NULL)
		return (NULL);
	return (ft_split((*envp) + 5, ':'));
}

// char	*find_path(char *p, char **path)
// {
// 	char	*check_path;
// 	char	*p2;
//
// 	while (*path)
// 	{
// 		check_path = ft_strjoin(*path, "/");
// 		if (!check_path)
// 			return (NULL);
// 		p2 = ft_strjoin(check_path, p);
// 		free(check_path);
// 		if (!p2)
// 			return (NULL);
// 		if (access(p2, F_OK) == 0)
// 			return (p2);
// 		free(p2);
// 		path++;
// 	}
// 	return (NULL);
// }

char	*find_path(char *p, char **path)
{
	char *check_path;
	size_t path_len;

	while (*path)
	{
		path_len = ft_snprintf((char *) NULL, 0, "%s/%s", *path, p);
		if (path_len < 0)
			return (NULL);
		check_path = malloc(sizeof(char) * (path_len + 1));
		if (!check_path)
			return (NULL);
		ft_snprintf(check_path, path_len + 1, "%s/%s", *path, p); 
 		if (access(check_path, F_OK) == 0)
 			return (check_path);
 		free(check_path);
 		path++;
	}
	return (NULL);
}

t_cmd	*parse_commands(char **args, int n_cmds, char **path)
{
	int		i;
	size_t	j;
	size_t	len;
	char	**split_cmd;
	t_cmd	*cmds;

	cmds = ft_calloc(n_cmds + 1, sizeof(t_cmd));
	i = 0;
	while (i < n_cmds)
	{
		split_cmd = ft_split(args[i], ' ');
		if (!split_cmd)
		{
			clear_cmd_array(cmds);
			return (NULL);
		}
		cmds[i].exec_path = find_path(split_cmd[0], path);
		if (!cmds[i].exec_path)
		{
			clear_cmd_array(cmds);
			return (NULL);
		}
		len = len2d((void *)split_cmd);
		cmds[i].args = ft_calloc(len + 2, sizeof(char *));
		if (cmds[i].args == NULL)
		{
			clear_cmd_array(cmds);
			return (NULL);
		}
		cmds[i].args[0] = ft_strdup(cmds[i].exec_path);
		j = 1;
		while (j < len)
		{
			cmds[i].args[j] = split_cmd[j];
			j++;
		}
		i++;
		free(split_cmd[0]);
		free(split_cmd);
	}
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	t_cmd	*cmds;
	t_context con;

	if (argc < 5)
		return (1);
	con.infile = argv[1];
	con.outfile = argv[argc - 1];
	con.n_cmds = 2;
	path = get_exec_path(envp);
	if (!path)
		return (1);
	cmds = parse_commands(argv + 2, con.n_cmds, path);
	free_2d_arr((void **)path, len2d((void **)path));
	//print_commands(cmds);
	pipex(&con, cmds);
	clear_cmd_array(cmds);
	return (0);
}


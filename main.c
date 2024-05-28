/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:30 by pleander          #+#    #+#             */
/*   Updated: 2024/05/24 15:49:19 by pleander         ###   ########.fr       */
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

char	*find_path(char *p, char **path)
{
	char *check_path;

	while (*path)
	{
		check_path = ft_strjoin(*path, "/");
		if (!check_path)
			return (NULL);
		check_path = ft_strjoin(check_path, p);
		if (!check_path)
			return (NULL);
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
	int		j;
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
		cmds[i].args = ft_calloc(len, sizeof(char *));
		if (cmds[i].args == NULL)
		{
			clear_cmd_array(cmds);
			return (NULL);
		}
		j = 1;
		while (j < len)
		{
			cmds[i].args[j - 1] = split_cmd[j];
			j++;
		}
		free(split_cmd);
		i++;
	}
	return (cmds);
}

int	main(int argc, char **argv, char **envp)
{
	char	*infile;
	char	*outfile;
	char	**path;
	t_cmd	*cmds;

	if (argc < 5)
		return (1);
	infile = argv[1];
	outfile = argv[argc];
	path = get_exec_path(envp);
	if (!path)
		return 1;
	int i = 0;
	cmds = parse_commands(argv + 2, 2, path);
	while (cmds[i].args != NULL)
	{
		ft_printf("cmd: %s arg: %s\n", cmds[i].exec_path, cmds[i].args[0]);
		i++;
	}

}


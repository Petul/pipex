/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:33:41 by pleander          #+#    #+#             */
/*   Updated: 2024/06/03 10:59:42 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft/include/ft_printf.h"
#include "libft/include/libft.h"
#include "pipex.h"


static char	*find_path(char *p, char **path)
{
	char *check_path;
	int path_len;

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
	return ("");
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
			return (NULL);
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

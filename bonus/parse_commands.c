/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:33:41 by pleander          #+#    #+#             */
/*   Updated: 2024/06/19 10:54:09 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../libft/include/ft_printf.h"
#include "../libft/include/libft.h"
#include "pipex.h"

static char	*find_path(char *p, char **path)
{
	char	*check_path;
	int		path_len;

	if (!p || *p == '\0')
		return (ft_strdup(""));
	if (*p == '.' || *p == '/')
		return (ft_strdup(p));
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
	check_path = ft_strdup(p);
	return (check_path);
}

static char	**extract_arguments(char *arg)
{
	char	**split;

	split = (argv_split(arg));
	if (!split)
		return (NULL);
	return (split);
}

t_cmd	*parse_commands(char **args, int n_cmds, char **path)
{
	t_cmd	*cmds;
	size_t	i;

	cmds = ft_calloc(n_cmds + 1, sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	i = 0;
	while ((int)i < n_cmds)
	{
		cmds[i].args = extract_arguments((args[i]));
		if (!cmds[i].args)
			return (NULL);
		cmds[i].exec_path = find_path(cmds[i].args[0], path);
		if (!cmds[i].exec_path)
			return (NULL);
		i++;
	}
	return (cmds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:10:07 by pleander          #+#    #+#             */
/*   Updated: 2024/06/20 16:41:03 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/include/libft.h"
#include "pipex.h"

static int	free_and_return_zero(char **split)
{
	int	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	return (0);
}

static int	handle_quote(char *args, char **split, size_t *i, int c)
{
	if (args[*i] == '\'')
		split[c] = ft_strcdup(args + *i + 1, "\'");
	else if (args[*i] == '\"')
		split[c] = ft_strcdup(args + *i + 1, "\"");
	if (!split[c])
		free_and_return_zero(split);
	*i += ft_strlen(split[c]) + 2;
	return (1);
}

static void	skip_spaces(char *args, size_t *i)
{
	while (args[*i] == ' ')
		(*i)++;
}

static int	perform_splitting(char *args, int n_args, char **split)
{
	size_t	i;
	int		c;

	i = 0;
	c = 0;
	while (i < ft_strlen(args) || c < n_args)
	{
		if (args[i] == '\'' || args[i] == '\"')
		{
			if (handle_quote(args, split, &i, c) == 0)
				free_and_return_zero(split);
		}
		else
		{
			split[c] = ft_strcdup(args + i, " \'\"");
			if (!split[c])
				free_and_return_zero(split);
			i += ft_strlen(split[c]) + 1;
		}
		c++;
		skip_spaces(args, &i);
	}
	return (1);
}

char	**argv_split(char *args)
{
	char	**split;
	int		n_args;

	n_args = count_args(args);
	if (n_args == 0)
		n_args = 1;
	split = ft_calloc(n_args + 1, sizeof(char *));
	if (!split)
		return (NULL);
	if (!perform_splitting(args, n_args, split))
	{
		free(split);
		return (NULL);
	}
	return (split);
}

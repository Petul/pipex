/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 13:39:02 by pleander          #+#    #+#             */
/*   Updated: 2024/06/07 17:21:48 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"

static int	count_args(char *s)
{
	int	count;
	int	len;
	int	i;
	char c;
	char q;

	c = ' ';
	count = 0;
	i = 0;
	len = (int)ft_strlen(s);
	if (len == 0)
		return (0);
	if (s[i] != c && i == 0)
		count++;
	while (i < len - 1)
	{
 		if (s[i] == '\'' || s[i] == '\"')
		{
			q =  s[i];
			i++;
			while (s[i] != q)
				i++;
		}
		if (s[i] == c && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_strcdup(char *s, char *charset)
{
	char	*dup;
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(charset, s[i]))
		i++;
	dup = ft_substr(s, 0, i);
	if (!dup)
		return (NULL);
	return (dup);
}

char	**argv_split(char *args)
{
	char **split;
	int		n_args;
	int		c;
	int		i;

	n_args = count_args(args);
	split = ft_calloc(n_args + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	c = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '\"')
		{
			char *q = ft_calloc(2, sizeof(char));
			q[0] = args[i];
			split[c] = ft_strcdup(args + i, q);
			if (!split[c])
			{
				//free_array
			return (NULL);
			}
			i += ft_strlen(split[c]);
			c++;
		}
		else
		{
			split[c] = ft_strcdup(args + i, " \'\"");
			if (!split[c])
			{
				//free array
				return (NULL);
			}
			i += ft_strlen(split[c]);
			c++;
		} 
		i++;
	}
	ft_printf("N arguments: %d\n", n_args);
	return (split);
}

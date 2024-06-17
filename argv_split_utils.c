/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:05:32 by pleander          #+#    #+#             */
/*   Updated: 2024/06/17 14:08:04 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"

char	*ft_strcdup(char *s, char *charset)
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

int	count_args(char *s)
{
	int	count;
	int	len;
	int	i;
	char q;

	count = 0;
	i = 0;
	len = (int)ft_strlen(s);
	if (len == 0)
		return (0);
	if (s[i] != ' ' && i == 0)
		count++;
	while (i < len - 1)
	{
 		if (s[i] == '\'' || s[i] == '\"')
		{
			q =  s[i++];
			while (s[i] != q)
				i++;
		}
		if (s[i] == ' ' && s[i + 1] != ' ')
			count++;
		i++;
	}
	return (count);
}

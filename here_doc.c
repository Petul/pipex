/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:25 by pleander          #+#    #+#             */
/*   Updated: 2024/06/17 16:08:26 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft/include/get_next_line.h"
#include "libft/include/libft.h"

static void	write_to_stdin(void *str)
{
	write(STDIN_FILENO, (char *)str, ft_strlen(str));
}

void	read_heredoc(char *limiter)
{
	t_list	*line;

	line = ft_lstnew(get_next_line(STDIN_FILENO));
	if (!line)
	{
		return ;
		// protect
	}
	while (ft_strncmp((char *)ft_lstlast(line)->content, limiter, ft_strlen(limiter)) != 0)
	{
		ft_lstadd_back(&line, ft_lstnew(get_next_line(STDIN_FILENO)));
		if (!ft_lstlast(line)->content)
		{
			return ;
			// protect
		}
	}
	ft_lstiter(line, &write_to_stdin);
	ft_lstclear(&line, &free); 
	return ;
}

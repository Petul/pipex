/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:56:25 by pleander          #+#    #+#             */
/*   Updated: 2024/06/19 11:09:07 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/include/get_next_line.h"
#include "../libft/include/libft.h"

static int	write_content_to_fd(t_list *lst, int fd)
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (write(fd, lst->content, ft_strlen(lst->content)) < 0)
			return (-1);
		lst = lst->next;
	}
	return (1);
}

void	read_heredoc(char *limiter, int write_fd)
{
	t_list	*line;

	line = ft_lstnew(get_next_line(STDIN_FILENO));
	if (!line)
	{
		close(write_fd);
		return ;
	}
	while (ft_strncmp((char *)ft_lstlast(line)->content,
			limiter, ft_strlen(limiter)) != 0)
	{
		ft_lstadd_back(&line, ft_lstnew(get_next_line(STDIN_FILENO)));
		if (!ft_lstlast(line)->content)
		{
			ft_lstclear(&line, &free);
			close(write_fd);
			return ;
		}
	}
	write_content_to_fd(line, write_fd);
	close(write_fd);
	ft_lstclear(&line, &free);
	return ;
}

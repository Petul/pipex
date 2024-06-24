/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:11:16 by pleander          #+#    #+#             */
/*   Updated: 2024/06/24 10:11:24 by pleander         ###   ########.fr       */
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

static int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
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
	while (ft_strncmp((char *)ft_lstlast(line)->content, limiter,
			max(ft_strlen(limiter),
				ft_strlen((char *)ft_lstlast(line)->content) - 1)) != 0)
	{
		ft_lstadd_back(&line, ft_lstnew(get_next_line(STDIN_FILENO)));
		if (!ft_lstlast(line)->content)
			break ;
	}
	write_content_to_fd(line, write_fd);
	close(write_fd);
	ft_lstclear(&line, &free);
	return ;
}

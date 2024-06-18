/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:34:47 by pleander          #+#    #+#             */
/*   Updated: 2024/06/06 15:47:01 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "pipex.h"
#include "libft/include/ft_printf.h"

static int	open_file_fds(int file_fds[2], char *infile, char *outfile)
{
	file_fds[0] = open(infile, O_RDONLY);
	file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fds[0] < 0 || file_fds[1] < 0)
	{
		if (file_fds[0] < 0)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, infile, strerror(errno));
		if (file_fds[1] < 0)
			ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, outfile, strerror(errno));
		if (file_fds[1] < 0)
			return (1);
		return (0);
	}
	return (1);
}

static int	open_heredoc_fds(t_fds *fds, char *outfile)
{
	fds->heredoc_pipe = malloc(sizeof(int) * 2);
	if (pipe(fds->heredoc_pipe) < 0)
		return (1);
	dup2(fds->heredoc_pipe[0], fds->file_fds[0]);
	fds->file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fds->file_fds[1] < 0)
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", NAME, outfile, strerror(errno));
	if (fds->file_fds[1] < 0)
		return (1);
	return (0);
}

void	close_fds(int file_fds[2])
{
	close(file_fds[0]);
	close(file_fds[1]);
}

int	open_fds(t_fds *fds, t_context *con)
{
	if (con->limiter)
		return (open_heredoc_fds(fds, con->outfile));
	fds->heredoc_pipe = NULL;
	return (open_file_fds(fds->file_fds, con->infile, con->outfile));
}


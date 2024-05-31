/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:34:47 by pleander          #+#    #+#             */
/*   Updated: 2024/05/31 15:06:30 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "pipex.h"
#include "libft/include/ft_printf.h"

void	close_fds(int file_fds[2])
{
	close(file_fds[0]);
	close(file_fds[1]);
}

int	open_fds(int file_fds[2], char *infile, char *outfile)
{
	char	*err;

	file_fds[0] = open(infile, O_RDONLY);
	if (file_fds[0] < 0)
	{
		err = strerror(errno);
		ft_dprintf(STDERR, "%s: %s: %s\n", NAME, infile, err);
		return (-1);
	}
	file_fds[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fds[1] < 0)
	{
		close(file_fds[0]);
		err = strerror(errno);
		ft_dprintf(STDERR, "%s: %s: %s\n", NAME, outfile, err);
		return (-1);
	}
	return (1);
}

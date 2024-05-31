/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:13:19 by pleander          #+#    #+#             */
/*   Updated: 2024/05/31 10:37:08 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define NAME "pipex"
# define ERR_CMD_NOT_FOUND "command not found"

# include <stddef.h>

typedef struct s_cmd
{
	char	*exec_path;
	char	**args;
}	t_cmd;

typedef struct s_context
{
	char	*infile;
	char	*outfile;
	char	**envp;
	size_t	n_cmds;
}			t_context;

int		pipex(t_context *con, t_cmd *cmds);
void	clear_cmd_array(t_cmd *arr);
size_t	len2d(void **arr);
void	print_commands(t_cmd *cmds);
int		**create_pipes(size_t n_pipes);
void	delete_pipes(int **pipes, size_t n_pipes);
void	free_2d_arr(void **arr, size_t len);
int		open_fds(int file_fds[2], char *infile, char *outfile);
void	close_fds(int file_fds[2]);

#endif

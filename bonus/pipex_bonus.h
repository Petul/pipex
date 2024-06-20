/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:52:20 by pleander          #+#    #+#             */
/*   Updated: 2024/06/20 13:52:31 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define NAME "pipex"
# define STR_CMD_NOT_FOUND "command not found"
# define CODE_CMD_NOT_FOUND 127
# define CODE_PERMISSION_DENIED 126

# include <stddef.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	char	*exec_path;
	char	**args;
}	t_cmd;

typedef struct s_context
{
	char	*infile;
	char	*limiter;
	char	*outfile;
	char	**envp;
	char	**args;
	char	**path;
	size_t	n_cmds;
}			t_context;

typedef struct s_children
{
	pid_t	*child_pids;
	size_t	n_children;
}	t_children;

typedef struct s_fds
{
	int		**pipes;
	int		file_fds[2];	
	int		*heredoc_pipe;
}	t_fds;

int		pipex(t_context *con);
t_cmd	*parse_commands(char **args, int n_cmds, char **path);
void	clear_cmd_array(t_cmd *arr);
size_t	len2d(void **arr);
void	print_commands(t_cmd *cmds);
int		**create_pipes(size_t n_pipes);
void	delete_pipes(int **pipes, size_t n_pipes);
int		open_fds(t_fds *fds, t_context *con);
void	free_2d_arr(void **arr, size_t len);
void	close_fds(t_fds *fds);
int		spawn_child(t_fds *fds, t_context *con, t_children *children,
			t_cmd *cmds);
char	**argv_split(char *args);
char	*ft_strcdup(char *s, char *charset);
int		count_args(char *s);
void	read_heredoc(char *limiter, int write_fd);

#endif

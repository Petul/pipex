/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:13:19 by pleander          #+#    #+#             */
/*   Updated: 2024/06/07 14:38:35 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define NAME "pipex"
# define STR_CMD_NOT_FOUND "command not found"
# define CODE_CMD_NOT_FOUND 127

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
}	t_fds;

int		pipex(t_context *con);
t_cmd	*parse_commands(char **args, int n_cmds, char **path);
void	clear_cmd_array(t_cmd *arr);
size_t	len2d(void **arr);
void	print_commands(t_cmd *cmds);
int		**create_pipes(size_t n_pipes);
void	delete_pipes(int **pipes, size_t n_pipes);
void	free_2d_arr(void **arr, size_t len);
int		open_fds(int file_fds[2], char *infile, char *outfile);
void	close_fds(int file_fds[2]);
int		spawn_child(t_fds *fds, t_context *con, t_children *children, t_cmd *cmds);
char	**argv_split(char *args);

#endif

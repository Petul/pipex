/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:13:19 by pleander          #+#    #+#             */
/*   Updated: 2024/05/24 15:49:29 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stddef.h>

typedef struct s_cmd
{
	char	*exec_path;
	char	**args;
}	t_cmd;

void	clear_cmd_array(t_cmd *arr);
size_t	len2d(void **arr);

#endif

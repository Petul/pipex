/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:01:30 by pleander          #+#    #+#             */
/*   Updated: 2024/05/24 15:49:19 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"

char **get_exec_path(char **envp)
{
	while (ft_strncmp(*envp, "PATH=", 5) && *envp != NULL)
		envp++;
	if (*envp == NULL)
		return (NULL);
	return (ft_split((*envp) + 5, ':'));
}

int	main(int argc, char **argv, char **envp)
{
	char **path;

	path = get_exec_path(envp);
	if (!path)
		return 1;
}


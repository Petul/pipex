/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:48:45 by pleander          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:16 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../include/ft_printf.h"
#include "../include/ft_printf.h"

t_bool	print_char(int data, size_t *written)
{
	if (write(STDOUT, &data, 1) < 0)
		return (FALSE);
	*written += 1;
	return (TRUE);
}

t_bool	print_string(char *data, size_t n, size_t *written)
{
	size_t	i;

	i = 0;
	while (data[i] && i < n)
	{
		if (print_char(data[i], written) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

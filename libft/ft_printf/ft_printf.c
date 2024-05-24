/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:36:42 by pleander          #+#    #+#             */
/*   Updated: 2024/05/23 11:36:52 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "../include/ft_printf.h"
#include "../include/libft.h"

static t_bool	free_and_return(void *data, t_bool t)
{
	free(data);
	return (t);
}

static t_fspec	*parse_fspec(char *fstr, size_t len)
{
	char	*conversion;
	t_fspec	*s;

	conversion = ft_substr(fstr, 0, len);
	if (!conversion)
		return (NULL);
	s = parse_conversion(conversion);
	free(conversion);
	return (s);
}

static t_fspec	*get_format_spec(char *fstart)
{
	size_t	len;
	t_fspec	*s;
	char	format;

	format = '\0';
	len = 1;
	while (fstart[len])
	{
		if (ft_strchr("cspdiuXx%", fstart[len]))
		{
			format = fstart[len];
			break ;
		}
		len++;
	}
	s = parse_fspec(fstart, len);
	if (!s)
		return (NULL);
	s->format = format;
	s->len = len;
	return (s);
}

static t_bool	process_fspec(char *f, va_list *args, size_t *loc, size_t *w)
{
	t_fspec	*s;
	t_bool	t;

	t = TRUE;
	s = get_format_spec(f);
	if (!s)
		return (FALSE);
	if (s->format == 'c')
		t = convert_char(s, va_arg(*args, int), w);
	else if (s->format == 's')
		t = convert_string(s, va_arg(*args, char *), w);
	else if (s->format == 'p')
		t = convert_pointer(s, va_arg(*args, void *), w);
	else if (s->format == 'd' || s->format == 'i')
		t = convert_decimal(s, va_arg(*args, int), w);
	else if (s->format == 'u')
		t = convert_unsigned(s, va_arg(*args, unsigned int), w);
	else if (s->format == 'X')
		t = convert_hex_upper(s, va_arg(*args, int), w);
	else if (s->format == 'x')
		t = convert_hex_lower(s, va_arg(*args, int), w);
	else if (s->format == '%')
		t = convert_char(s, '%', w);
	*loc += s->len + 1;
	return (free_and_return(s, t));
}

int	ft_printf(const char *fstring, ...)
{
	va_list	args;
	size_t	loc;
	size_t	written;
	t_bool	t;

	va_start(args, fstring);
	written = 0;
	loc = 0;
	while (loc < ft_strlen(fstring))
	{
		if (fstring[loc] == '%')
		{
			t = process_fspec((char *)fstring + loc, &args, &loc, &written);
			if (t == FALSE)
				return (-1);
			continue ;
		}
		if (print_char(fstring[loc++], &written) == FALSE)
			return (-1);
	}
	va_end(args);
	return (written);
}

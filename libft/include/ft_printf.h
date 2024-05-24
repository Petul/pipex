/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleander <pleander@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:08:41 by pleander          #+#    #+#             */
/*   Updated: 2024/05/18 18:18:44 by pleander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include <stddef.h>

# define STDOUT 1
# define BASE_DEC "0123456789"
# define BASE_HEX_UPPER "0123456789ABCDEF"
# define BASE_HEX_LOWER "0123456789abcdef"
# define NULL_STR "(null)"

typedef unsigned char	t_bool;
# define TRUE 1
# define FALSE 0

typedef struct s_fspec
{
	char	format;
	size_t	len;
	t_bool	alternate_form;
	t_bool	zero_padding;
	t_bool	negative_field_width;
	t_bool	space_before_pos;
	t_bool	plus_before_pos;
	t_bool	has_dot;
	size_t	min_field_width;
	size_t	precision;
}	t_fspec;

int		ft_printf(const char *fstring, ...);
t_bool	print_char(int data, size_t *written);
t_bool	print_string(char *data, size_t n, size_t *written);
t_fspec	*parse_conversion(char *conversion);
t_bool	convert_char(t_fspec *s, int data, size_t *written);
t_bool	convert_string(t_fspec *s, char *data, size_t *written);
t_bool	convert_pointer(t_fspec *s, char *data, size_t *written);
t_bool	convert_decimal(t_fspec *s, int data, size_t *written);
t_bool	convert_unsigned(t_fspec *s, unsigned int data, size_t *written);
t_bool	convert_hex_upper(t_fspec *s, int data, size_t *written);
t_bool	convert_hex_lower(t_fspec *s, int data, size_t *written);
char	*ft_utoa_base(unsigned int n, char *base);
char	*ft_ultoa_base(unsigned long n, char *base);
char	*apply_plus(t_fspec *s, char *num);
char	*apply_alternate_hex_form(t_fspec *s, char *num, char *pre_str);
char	*apply_field_width(t_fspec *s, char *data);
char	*apply_precision(t_fspec *s, char *num);
char	*apply_space_before_pos(t_fspec *s, char *num);
char	*apply_string_precision(t_fspec *s, char *str);
int		only_zero_or_space(char *num);
void	float_sign(char *num);
void	float_space(char *num);

#endif

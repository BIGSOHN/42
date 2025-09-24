/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 17:43:37 by ssohn             #+#    #+#             */
/*   Updated: 2024/05/07 20:13:37 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *format, ...);
int		is_seperator(char format);
int		type_sep(const char *format, va_list arg_ptr);
int		type_char(va_list arg_ptr);
int		type_string(va_list arg_ptr);
int		type_percent_sign(va_list arg_ptr);
int		type_decimal(va_list arg_ptr);
int		type_integer(va_list arg_ptr);
int		type_unsigned_int(va_list arg_ptr);
int		type_low_hex(va_list arg_ptr);
int		type_up_hex(va_list arg_ptr);
int		type_pointer(va_list arg_ptr);
int		pointer_len(unsigned long long n);
int		count_len(long long n, int number);
void	ft_pointer_putnbr(unsigned long long n);
void	ft_putnbr(int n);
void	ft_uputnbr(unsigned int num);
void	ft_low_hex_putnbr(unsigned int n);
void	ft_up_hex_putnbr(unsigned int n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:15:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/03 16:52:32 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list		arg_ptr;
	int			print_count;

	print_count = 0;
	va_start(arg_ptr, format);
	if (format == NULL)
		return (-1);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			if (is_seperator(*format) == 0)
				return (-1);
			print_count += type_sep(format, arg_ptr);
		}
		else
		{
			write(1, format, 1);
			print_count++;
		}
		format++;
	}
	va_end(arg_ptr);
	return (print_count);
}

int	is_seperator(char format)
{
	const char	*seperator = "cspdiuxX%";
	int			i;

	i = 0;
	while (seperator[i] != '\0')
	{
		if (seperator[i] == format)
			return (1);
		i++;
	}
	return (0);
}

int	type_sep(const char *format, va_list arg_ptr)
{
	int	count;

	if (*format == 'c')
		count = type_char(arg_ptr);
	else if (*format == 's')
		count = type_string(arg_ptr);
	else if (*format == 'p')
		count = type_pointer(arg_ptr);
	else if (*format == 'd')
		count = type_decimal(arg_ptr);
	else if (*format == 'i')
		count = type_integer(arg_ptr);
	else if (*format == 'u')
		count = type_unsigned_int(arg_ptr);
	else if (*format == 'x')
		count = type_low_hex(arg_ptr);
	else if (*format == 'X')
		count = type_up_hex(arg_ptr);
	else if (*format == '%')
		count = type_percent_sign(arg_ptr);
	return (count);
}

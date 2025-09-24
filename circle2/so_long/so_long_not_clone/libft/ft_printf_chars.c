/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:28:11 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/03 16:29:34 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	type_char(va_list arg_ptr)
{
	int		count;
	char	var;

	var = va_arg(arg_ptr, int);
	write(1, &var, 1);
	count = 1;
	return (count);
}

int	type_string(va_list arg_ptr)
{
	int		count;
	int		len;
	char	*var;

	var = va_arg(arg_ptr, char *);
	len = ft_strlen(var);
	if (var == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(1, var, len);
	count = len;
	return (count);
}

int	type_percent_sign(va_list arg_ptr)
{
	int		count;

	write(1, "%", 1);
	count = 1;
	return (count);
}

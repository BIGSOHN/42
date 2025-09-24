/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:02:18 by ssohn             #+#    #+#             */
/*   Updated: 2024/05/07 18:07:22 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_decimal(va_list arg_ptr)
{
	int		count;
	int		var;

	var = va_arg(arg_ptr, int);
	count = count_len(var, 10);
	ft_putnbr(var);
	return (count);
}

int	type_integer(va_list arg_ptr)
{
	int		count;
	int		var;

	var = va_arg(arg_ptr, int);
	count = count_len(var, 10);
	ft_putnbr(var);
	return (count);
}

int	type_unsigned_int(va_list arg_ptr)
{
	int				count;
	unsigned int	var;

	var = va_arg(arg_ptr, unsigned int);
	count = count_len(var, 10);
	ft_uputnbr(var);
	return (count);
}

int	type_low_hex(va_list arg_ptr)
{
	int				count;
	unsigned int	var;

	var = va_arg(arg_ptr, unsigned int);
	count = count_len(var, 16);
	ft_low_hex_putnbr(var);
	return (count);
}

int	type_up_hex(va_list arg_ptr)
{
	int				count;
	unsigned int	var;

	var = va_arg(arg_ptr, unsigned int);
	count = count_len(var, 16);
	ft_up_hex_putnbr(var);
	return (count);
}

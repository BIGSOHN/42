/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:52:07 by ssohn             #+#    #+#             */
/*   Updated: 2024/05/07 19:59:07 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_pointer(va_list arg_ptr)
{
	int					count;
	unsigned long long	var;
	char				c;

	var = (unsigned long long)va_arg(arg_ptr, void *);
	if (var == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	count = pointer_len(var);
	write(1, "0x", 2);
	count++;
	ft_pointer_putnbr(var);
	return (count);
}

void	ft_pointer_putnbr(unsigned long long n)
{
	const char	hexchar[16] = "0123456789abcdef";
	char		c;
	int			count;

	count = 0;
	if (n == 0)
		return ;
	if (n >= 16)
	{
		ft_pointer_putnbr(n / 16);
		n = n % 16;
	}
	if (n < 16)
	{
		c = hexchar[n];
		write(1, &c, 1);
		count++;
	}
}

int	pointer_len(unsigned long long n)
{
	int	count;

	count = 0;
	while (n != 0)
	{
		n = n / 16;
		count++;
	}
	count++;
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_simple_util.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:19:55 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:43:06 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(long long n, int number)
{
	int			count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n >= number)
	{
		n = n / number;
		count++;
	}
	count++;
	return (count);
}

void	ft_putnbr(int n)
{
	long long	num;
	char		c;

	num = n;
	if (num < 0)
	{
		write(1, "-", 1);
		num *= -1;
	}
	else if (num == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		num = num % 10;
	}
	if (num < 10)
	{
		c = num + '0';
		write(1, &c, 1);
	}
}

void	ft_uputnbr(unsigned int num)
{
	char	c;

	if (num == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (num >= 10)
	{
		ft_uputnbr(num / 10);
		num = num % 10;
	}
	if (num < 10)
	{
		c = num + '0';
		write(1, &c, 1);
	}
}

void	ft_low_hex_putnbr(unsigned int n)
{
	const char			hexchar[16] = "0123456789abcdef";
	unsigned long long	num;
	char				c;

	num = n;
	if (num == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (num >= 16)
	{
		ft_low_hex_putnbr(num / 16);
		num = num % 16;
	}
	if (num < 16)
	{
		c = hexchar[num];
		write(1, &c, 1);
	}
}

void	ft_up_hex_putnbr(unsigned int n)
{
	const char			hexchar[16] = "0123456789ABCDEF";
	unsigned long long	num;
	char				c;

	num = n;
	if (num == 0)
	{
		write (1, "0", 1);
		return ;
	}
	if (num >= 16)
	{
		ft_up_hex_putnbr(num / 16);
		num = num % 16;
	}
	if (num < 16)
	{
		c = hexchar[num];
		write(1, &c, 1);
	}
}

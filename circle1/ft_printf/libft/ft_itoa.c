/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 16:15:42 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/15 09:45:59 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_insert_num(char *dest, long long num, int count);
static int			ft_count_num(long long n);
static long long	ft_count_digit(long long count, long long num);
char				*ft_itoa(int n);

char	*ft_itoa(int n)
{
	long long	count;
	long long	i;
	long long	num;
	char		*result;

	i = 0;
	num = n;
	count = ft_count_num(num);
	result = (char *)malloc(sizeof(char) * (count + 1));
	if (result == 0)
		return (0);
	result = ft_insert_num(result, num, count);
	return (result);
}

static char	*ft_insert_num(char *dest, long long num, int count)
{
	long long	n_digit;
	int			i;

	i = 0;
	n_digit = ft_count_digit(count, num);
	if (num < 0)
	{
		dest[i] = '-';
		num *= -1;
		i++;
	}
	while (n_digit > 0)
	{
		dest[i] = num / n_digit + '0';
		num = num - (num / n_digit * n_digit);
		n_digit = n_digit / 10;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static long long	ft_count_digit(long long count, long long num)
{
	long long	n_digit;
	long long	i;

	i = 1;
	n_digit = 1;
	if (num < 0)
		count--;
	while (i < count)
	{
		n_digit = 10 * n_digit;
		i++;
	}
	return (n_digit);
}

static int	ft_count_num(long long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

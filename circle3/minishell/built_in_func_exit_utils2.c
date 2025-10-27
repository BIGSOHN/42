/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_exit_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 18:34:49 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/31 19:08:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char			*ft_insert_num(char *dest, long long num, int count);
static int			ft_count_num(long long n);
static long long	ft_count_digit(long long count, long long num);
char				*ft_lltoa(long long n);

char	*ft_lltoa(long long n)
{
	int			count;
	long long	num;
	char		*result;

	num = n;
	count = ft_count_num(num);
	result = (char *)ft_malloc(sizeof(char) * (count + 1));
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
		if (n == LONG_LONG_MIN)
			return (20);
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

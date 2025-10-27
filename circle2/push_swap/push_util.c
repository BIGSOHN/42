/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:40:51 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/17 18:49:23 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long long	ft_atoll(const char *nptr)
{
	int			i;
	int			n;
	long long	result;

	i = 0;
	result = 0;
	n = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			n *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * n);
}

int	ft_count_word(char *s, char c)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (((s[i] == c && len > 0) || (s[i] != c && s[i + 1] == '\0')))
		{
			len = 0;
			count++;
		}
		if (s[i] != c)
			len++;
		i++;
	}
	return (count);
}

char	**double_pointer_free(char **dest, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
	return (0);
}

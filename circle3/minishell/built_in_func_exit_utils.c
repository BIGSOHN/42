/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_exit_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:28:12 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/23 17:54:25 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_zero_strlen(const char *s)
{
	size_t	length;
	int		i;

	i = 0;
	length = 0;
	if (s == NULL)
		return (0);
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] == '0')
	{
		i++;
	}
	while (s[i] != '\0')
	{
		i++;
		length++;
	}
	return (length);
}

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

int	ft_check_valid_number(char *nptr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		flag = 1;
		i++;
	}
	if (flag != 1 || nptr[i] != '\0')
		return (0);
	return (1);
}

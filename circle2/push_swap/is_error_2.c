/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:00:36 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/28 13:00:37 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_argv_space(int argc, char **argv)
{
	int	i;
	int	j;
	int	flag;

	i = 1;
	while (i < argc)
	{
		j = 0;
		flag = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] != ' ')
				flag = 1;
			j++;
		}
		if (flag == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_first_zero_and_more(char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	if (nptr[i] == '0' && nptr[i + 1] != '\0')
		return (1);
	return (0);
}

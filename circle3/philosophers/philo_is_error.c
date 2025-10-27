/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_is_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:52:32 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 18:23:06 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	is_error(int argc, char **argv)
{
	if (argc <= 1)
		return (1);
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	if (is_input_invalid(argc, argv) == 1 || is_minus_num(argc, argv) == 1)
	{
		ft_putstr_fd("Error\n", 2);
		return (1);
	}
	return (0);
}

int	is_input_invalid(int argc, char **argv)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		if (ft_check_valid_number(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_minus_num(int argc, char **argv)
{
	int			i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoll(argv[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	length;

	length = ft_strlen(s);
	write (fd, s, length);
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

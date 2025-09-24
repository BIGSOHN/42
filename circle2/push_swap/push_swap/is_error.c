/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:05:35 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/17 18:49:47 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_error(int argc, char **argv)
{
	int	number_count;
	int	*num_list;

	if (argc <= 1)
		return (1);
	if (is_argv_space(argc, argv) == 1 || is_input_invalid(argc, argv) == 1
		|| is_int_range(argc, argv) == 0)
	{
		ft_printf("ERROR\n");
		return (1);
	}
	number_count = count_number(argc, argv);
	num_list = input_number(argc, argv, number_count);
	if (is_duplicated(num_list, number_count) == 1)
	{
		ft_printf("ERROR\n");
		free(num_list);
		return (1);
	}
	free(num_list);
	return (0);
}

int	is_input_invalid(int argc, char **argv)
{
	int		i;
	int		j;
	int		word_count;
	char	**temp_list;

	i = 1;
	while (i < argc)
	{
		temp_list = ft_split(argv[i], ' ');
		word_count = ft_count_word(argv[i], ' ');
		j = 0;
		while (j < word_count)
		{
			if (ft_check_valid_number(temp_list[j]) == 0)
			{
				double_pointer_free(temp_list, word_count);
				return (1);
			}
			j++;
		}
		double_pointer_free(temp_list, word_count);
		i++;
	}
	return (0);
}

int	is_int_range(int argc, char **argv)
{
	int			word_count;
	int			i;
	int			j;
	char		**temp_list;

	i = 1;
	while (i < argc)
	{
		temp_list = ft_split(argv[i], ' ');
		word_count = ft_count_word(argv[i], ' ');
		j = 0;
		while (j < word_count)
		{
			if (ft_atoll(temp_list[j]) > INT_MAX
				|| ft_atoll(temp_list[j]) < INT_MIN)
			{
				double_pointer_free(temp_list, word_count);
				return (0);
			}
			j++;
		}
		double_pointer_free(temp_list, word_count);
		i++;
	}
	return (1);
}

int	is_duplicated(int *num_list, int count_number)
{
	int	i;
	int	j;

	i = 0;
	while (i < count_number)
	{
		j = 0;
		while (j < count_number)
		{
			if (i != j && num_list[i] == num_list[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
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

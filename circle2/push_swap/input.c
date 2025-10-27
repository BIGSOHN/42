/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:46 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 17:49:22 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_number(int argc, char **argv)
{
	int	i;
	int	j;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	while (++i < argc)
	{
		j = 0;
		flag = 1;
		while (argv[i][j] != '\0')
		{
			if (ft_isdigit(argv[i][j]) == 0)
				flag = 1;
			else if (ft_isdigit(argv[i][j]) == 1 && flag == 1)
			{
				count++;
				flag = 0;
			}
			j++;
		}
	}
	return (count);
}

int	*input_number(int argc, char **argv, int number_count)
{
	int		*num_list;
	int		i;
	int		j;
	int		k;
	char	**temp_list;

	i = -1;
	j = 0;
	num_list = (int *)malloc(sizeof(int) * (number_count));
	if (num_list == 0)
		return (0);
	while (++j < argc)
	{
		temp_list = ft_split(argv[j], ' ');
		k = -1;
		while (++k < ft_count_word(argv[j], ' '))
			num_list[++i] = ft_atoi(temp_list[k]);
		double_pointer_free(temp_list, ft_count_word(argv[j], ' '));
	}
	return (num_list);
}

int	*input_index(int *num_list, int num_count)
{
	int	*index_list;
	int	number;
	int	index;
	int	i;
	int	j;

	i = -1;
	index_list = (int *)malloc(sizeof(int) * (num_count));
	if (index_list == 0)
		return (0);
	while (++i < num_count)
	{
		number = num_list[i];
		j = 0;
		index = 0;
		while (j < num_count)
		{
			if (number != num_list[j] && number > num_list[j])
				index++;
			j++;
		}
		index_list[i] = index;
	}
	return (index_list);
}

int	input_stack_node(int argc, char **argv, t_stack *stack)
{
	int		*num_list;
	int		*index_list;
	int		i;

	num_list = input_number(argc, argv, count_number(argc, argv));
	index_list = input_index(num_list, count_number(argc, argv));
	i = -1;
	while (++i < count_number(argc, argv))
		push(stack, num_list[i], index_list[i]);
	free(num_list);
	free(index_list);
	return (1);
}

int	is_first_sorted(int argc, char **argv)
{
	int	i;
	int	*num_list;

	i = 0;
	num_list = input_number(argc, argv, count_number(argc, argv));
	while (i + 1 < count_number(argc, argv))
	{
		if (num_list[i] > num_list[i + 1])
		{
			free(num_list);
			return (0);
		}
		i++;
	}
	free(num_list);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   three_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:17:43 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/27 11:17:52 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	three_is_sorted(t_stack *stack)
{
	int	temp_a;
	int	temp_b;
	int	temp_c;

	if (stack->size != 3)
		return (0);
	temp_a = stack->head->index;
	temp_b = stack->head->next->index;
	temp_c = stack->head->next->next->index;
	if (temp_a < temp_b && temp_a < temp_c)
		min_index_first(temp_a, temp_b, temp_c, stack);
	else if (temp_a > temp_b && temp_a > temp_c)
		max_index_first(temp_a, temp_b, temp_c, stack);
	else
		mid_index_first(temp_a, temp_b, temp_c, stack);
	return (1);
}

int	min_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack)
{
	if (temp_b < temp_c)
		return (1);
	else
	{
		reverse_rotate_stack(stack);
		ft_swap(stack);
		return (1);
	}
	return (0);
}

int	mid_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack)
{
	if (temp_b < temp_c)
	{
		ft_swap(stack);
		return (1);
	}
	else
	{
		reverse_rotate_stack(stack);
		return (1);
	}
	return (0);
}

int	max_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack)
{
	if (temp_b < temp_c)
	{
		rotate_stack(stack);
		return (1);
	}
	else
	{
		rotate_stack(stack);
		ft_swap(stack);
		return (1);
	}
	return (0);
}

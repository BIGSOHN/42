/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:21:26 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/28 18:28:51 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	left_sorted_three_node(t_stack *stack_a, t_stack *stack_b)
{
	int		input_num;
	int		num_pivot;
	int		big_count;
	t_node	*ptmp;

	input_num = stack_a->size;
	num_pivot = stack_a->size / 3;
	big_count = stack_a->size - (num_pivot * 2);
	while (stack_a-> size > 3 && stack_a->size > big_count)
	{
		ptmp = stack_a->head;
		if (ptmp->index < num_pivot)
			group_small(stack_a, stack_b);
		else if (ptmp->index >= num_pivot && ptmp->index < num_pivot * 2)
			group_mid(stack_a, stack_b);
		else
			rotate_stack(stack_a);
	}
	while (stack_a->size > 3)
		group_big(stack_a, stack_b, input_num);
	three_is_sorted(stack_a);
	return (1);
}

int	group_small(t_stack *stack_a, t_stack *stack_b)
{
	if (is_empty(stack_b) == 1)
	{
		push_stack_b(stack_b, stack_a);
		return (1);
	}
	push_stack_b(stack_b, stack_a);
	rotate_stack(stack_b);
	return (1);
}

int	group_mid(t_stack *stack_a, t_stack *stack_b)
{
	push_stack_b(stack_b, stack_a);
	return (1);
}

int	group_big(t_stack *stack_a, t_stack *stack_b, int input_num)
{
	if (stack_a->head->index > input_num - 4)
		rotate_stack(stack_a);
	else
		push_stack_b(stack_b, stack_a);
	return (1);
}

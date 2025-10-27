/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_greedy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:00:59 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/01 16:27:09 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*find_min_count_node(t_stack *stack_b)
{
	int		i;
	int		min_count;
	int		count_all;
	t_node	*ptmp;
	t_node	*min_node;

	i = 0;
	min_count = -1;
	ptmp = stack_b->head;
	while (i < stack_b->size)
	{
		if (min_count == -1 || count_all_inst(ptmp->info) < min_count)
		{
			min_count = count_all_inst(ptmp->info);
			min_node = ptmp;
		}
		i++;
		ptmp = ptmp->next;
	}
	return (min_node);
}

int	exec_greedy(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*pmin;
	int		a_min_loc;

	while (stack_b->size != 0)
	{
		write_all_count(stack_a, stack_b);
		pmin = find_min_count_node(stack_b);
		exec_inst(pmin, stack_a, stack_b);
		re_zero_info(stack_b);
	}
	a_min_loc = find_min_idx_loc(stack_a);
	if (a_min_loc < stack_a->size / 2)
		exec_stack_rotate(a_min_loc, stack_a);
	else
		exec_stack_reverse_rotate(stack_a->size - a_min_loc, stack_a);
	return (1);
}

int	exec_inst(t_node *pmin, t_stack *stack_a, t_stack *stack_b)
{
	exec_stack_rotate(pmin->info->ra_count, stack_a);
	exec_stack_rotate(pmin->info->rb_count, stack_b);
	exec_stack_reverse_rotate(pmin->info->rra_count, stack_a);
	exec_stack_reverse_rotate(pmin->info->rrb_count, stack_b);
	push_stack_a(stack_a, stack_b);
	return (1);
}

int	exec_stack_rotate(int mv_count, t_stack *stack)
{
	int	i;

	i = 0;
	while (i < mv_count)
	{
		rotate_stack(stack);
		i++;
	}
	return (1);
}

int	exec_stack_reverse_rotate(int mv_count, t_stack *stack)
{
	int	i;

	i = 0;
	while (i < mv_count)
	{
		reverse_rotate_stack(stack);
		i++;
	}
	return (1);
}

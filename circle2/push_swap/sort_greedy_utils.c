/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_greedy_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:15:28 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/01 16:27:15 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	int		i;
	t_node	*pmin;

	pmin = find_min_a_node(stack);
	i = 0;
	while (i + 1 < stack->size)
	{
		if (pmin->index > pmin->next->index)
			return (0);
		i++;
		pmin = pmin->next;
	}
	return (1);
}

t_node	*find_min_a_node(t_stack *stack_a)
{
	int		i;
	int		min;
	t_node	*pmin;
	t_node	*ptmp;

	i = 0;
	min = -1;
	ptmp = stack_a->head;
	while (i < stack_a->size)
	{
		if (min == -1 || ptmp->index < min)
		{
			min = ptmp->index;
			pmin = ptmp;
		}
		i++;
		ptmp = ptmp->next;
	}
	return (pmin);
}

int	find_min_idx_loc(t_stack *stack)
{
	int		i;
	int		min;
	int		min_loc;
	t_node	*ptmp;

	i = 0;
	min = -1;
	ptmp = stack->head;
	while (i < stack->size)
	{
		if (min == -1 || ptmp->index < min)
		{
			min = ptmp->index;
			min_loc = i;
		}
		i++;
		ptmp = ptmp->next;
	}
	return (min_loc);
}

int	loc_min_idx_bigger_than_b(t_stack *stack_a, int b_index)
{
	int		i;
	int		min_idx;
	int		min_locate;
	t_node	*ptmp;

	i = 0;
	min_locate = -1;
	min_idx = biggest_index(stack_a);
	ptmp = stack_a->head;
	while (i < stack_a->size)
	{
		if (b_index < ptmp->index && ptmp->index < min_idx)
		{
			min_locate = i;
			min_idx = ptmp->index;
		}
		ptmp = ptmp->next;
		i++;
	}
	return (min_locate);
}

int	biggest_index(t_stack *stack_a)
{
	int		big_idx;
	int		i;
	t_node	*ptmp;

	i = 0;
	big_idx = -1;
	ptmp = stack_a->head;
	while (i < stack_a->size)
	{
		if (big_idx == -1 || ptmp->index > big_idx)
			big_idx = ptmp->index;
		i++;
		ptmp = ptmp->next;
	}
	return (big_idx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_count_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:23:48 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/01 16:23:57 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	count_all_inst(t_node_info *node_info)
{
	int	all_inst;

	all_inst = node_info->ra_count + node_info->rb_count
		+ node_info->rra_count + node_info->rrb_count;
	return (all_inst);
}

int	count_top_stack_b(t_stack *stack_b)
{
	int		i;
	t_node	*ptmp;

	i = 0;
	ptmp = stack_b->head;
	while (i < stack_b->size)
	{
		if (i < stack_b->size / 2)
			ptmp->info->rb_count = i;
		else
			ptmp->info->rrb_count = stack_b->size - i;
		ptmp = ptmp->next;
		i++;
	}
	return (1);
}

int	count_stack_a_make_top(t_stack *stack_b, t_stack *stack_a)
{
	int		i;
	int		loc_a;
	t_node	*ptmp;

	i = 0;
	ptmp = stack_b->head;
	while (i < stack_b->size)
	{
		loc_a = loc_min_idx_bigger_than_b(stack_a, ptmp->index);
		if (loc_a != 0)
		{
			if (loc_a < stack_a->size / 2)
				ptmp->info->ra_count = loc_a;
			else
				ptmp->info->rra_count = stack_a->size - loc_a;
		}
		i++;
		ptmp = ptmp->next;
	}
	return (1);
}

void	write_all_count(t_stack *stack_a, t_stack *stack_b)
{
	count_top_stack_b(stack_b);
	count_stack_a_make_top(stack_b, stack_a);
}

void	re_zero_info(t_stack *stack_b)
{
	t_node	*ptmp;
	int		i;

	i = 0;
	ptmp = stack_b->head;
	while (i < stack_b->size)
	{
		ft_memset(ptmp->info, 0, sizeof(t_node_info));
		i++;
		ptmp = ptmp->next;
	}
}

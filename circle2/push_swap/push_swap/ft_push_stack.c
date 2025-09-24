/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:02:17 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/27 11:18:58 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_stack_a(t_stack *stack_a, t_stack *stack_b)
{
	int	ptmp_num;
	int	ptmp_index;

	if (is_empty(stack_b) == 1)
		return (0);
	ft_printf("pa\n");
	ptmp_num = stack_b->head->content;
	ptmp_index = stack_b->head->index;
	push_stack(stack_a, ptmp_num, ptmp_index);
	delete_at_head(stack_b);
	return (1);
}

int	push_stack_b(t_stack *stack_b, t_stack *stack_a)
{
	int	ptmp_num;
	int	ptmp_index;

	if (is_empty(stack_a) == 1)
		return (0);
	ft_printf("pb\n");
	ptmp_num = stack_a->head->content;
	ptmp_index = stack_a->head->index;
	push_stack(stack_b, ptmp_num, ptmp_index);
	delete_at_head(stack_a);
	return (1);
}

void	push_stack(t_stack *stack, int num, int index)
{
	if (stack->size == 0)
		insert_at_first(stack, num, index);
	else
		insert_at_front(stack, num, index);
}

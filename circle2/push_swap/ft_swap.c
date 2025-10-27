/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:35:44 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 13:45:43 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_swap(t_stack *stack)
{
	int	ptmp_first_num;
	int	ptmp_first_index;
	int	ptmp_second_num;
	int	ptmp_second_index;

	if (stack->size < 2)
		return (0);
	ft_printf("s%c\n", stack->stack_name);
	ptmp_first_num = stack->head->content;
	ptmp_first_index = stack->head->index;
	ptmp_second_num = stack->head->next->content;
	ptmp_second_index = stack->head->next->index;
	delete_at_head(stack);
	delete_at_head(stack);
	if (stack->size == 0)
		insert_at_first(stack, ptmp_first_num, ptmp_first_index);
	else
		insert_at_front(stack, ptmp_first_num, ptmp_first_index);
	insert_at_front(stack, ptmp_second_num, ptmp_second_index);
	return (1);
}

int	ft_swap_ss(t_stack *stack_a, t_stack *stack_b)
{
	t_node	*ptmp;
	t_node	*ptmp_next;

	if (stack_a->size < 2 && stack_b->size < 2)
		return (0);
	ft_printf("ss\n");
	ptmp = stack_a->head->next;
	ptmp_next = stack_a->head->next->next;
	stack_a->tail->next = stack_a->head->next;
	stack_a->head->next->prev = stack_a->tail;
	stack_a->head->next->next = stack_a->head;
	stack_a->head->prev = stack_a->head->next;
	stack_a->head->next = ptmp_next;
	stack_a->head = ptmp;
	ptmp = stack_b->head->next;
	ptmp_next = stack_b->head->next->next;
	stack_b->tail->next = stack_b->head->next;
	stack_b->head->next->prev = stack_b->tail;
	stack_b->head->next->next = stack_b->head;
	stack_b->head->prev = stack_b->head->next;
	stack_b->head->next = ptmp_next;
	stack_b->head = ptmp;
	return (1);
}

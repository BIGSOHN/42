/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:17:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 17:53:57 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	delete_at_head(t_stack *stack)
{
	t_node		*pdel;
	t_node_info	*pdel_info;

	if (is_empty(stack) == 1)
		return (0);
	if (stack->size == 1)
		return (delete_at_last(stack));
	pdel = stack->head;
	pdel_info = stack->head->info;
	stack->tail->next = stack->head->next;
	stack->head->next->prev = stack->tail;
	stack->head = stack->head->next;
	free(pdel_info);
	free(pdel);
	stack->size--;
	return (1);
}

int	delete_at_tail(t_stack *stack)
{
	t_node		*pdel;
	t_node_info	*pdel_info;

	if (is_empty(stack) == 1)
		return (0);
	if (stack->size == 1)
		return (delete_at_last(stack));
	pdel = stack->tail;
	pdel_info = stack->head->info;
	stack->head->prev = stack->tail->prev;
	stack->tail->prev->next = stack->head;
	stack->tail = stack->tail->prev;
	free(pdel_info);
	free(pdel);
	stack->size--;
	return (1);
}

int	delete_at_last(t_stack *stack)
{
	t_node		*pdel;
	t_node_info	*pdel_info;

	pdel = stack->head;
	pdel_info = stack->head->info;
	stack->head = NULL;
	stack->tail = NULL;
	free(pdel_info);
	free(pdel);
	stack->size--;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:38:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/25 11:38:28 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	rotate_stack(t_stack *stack)
{
	if (is_empty(stack) == 1 || stack->size == 1)
		return (0);
	ft_printf("r%c\n", stack->stack_name);
	stack->head = stack->head->next;
	stack->tail = stack->tail->next;
	return (1);
}

int	reverse_rotate_stack(t_stack *stack)
{
	if (is_empty(stack) == 1 || stack->size == 1)
		return (0);
	ft_printf("rr%c\n", stack->stack_name);
	stack->head = stack->head->prev;
	stack->tail = stack->tail->prev;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 13:26:49 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/30 13:27:00 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	two_is_sorted(t_stack *stack)
{
	int	temp_a;
	int	temp_b;

	if (stack->size != 2)
		return (0);
	temp_a = stack->head->index;
	temp_b = stack->head->next->index;
	if (temp_a < temp_b)
		return (1);
	else
	{
		ft_swap(stack);
		return (1);
	}
	return (0);
}

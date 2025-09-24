/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:58:44 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 17:54:40 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (is_error(argc, argv) == 1 || is_first_sorted(argc, argv) == 1)
		return (0);
	stack_a = init_stack('a');
	stack_b = init_stack('b');
	input_stack_node(argc, argv, stack_a);
	if (stack_a->size == 2)
		two_is_sorted(stack_a);
	left_sorted_three_node(stack_a, stack_b);
	exec_greedy(stack_a, stack_b);
	release_stack(stack_a);
	release_stack(stack_b);
	return (0);
}

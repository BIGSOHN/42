/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:37:48 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 13:38:09 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	printlist(t_stack *stack, int num_count)
{
	t_node	*ptmp;
	int		i;

	i = 0;
	ptmp = stack->head;
	ft_printf("printf stack %c\n", stack->stack_name);
	while (i < num_count)
	{
		ft_printf("content : %d\tindex : %d\n", ptmp->content, ptmp->index);
		ptmp = ptmp->next;
		i++;
	}
}

void	printbacklist(t_stack *stack, int num_count)
{
	t_node	*ptmp;
	int		i;

	i = 0;
	ptmp = stack->tail;
	ft_printf("printf back stack %c\n", stack->stack_name);
	while (i < num_count)
	{
		ft_printf("content : %d\tindex : %d\n", ptmp->content, ptmp->index);
		ptmp = ptmp->prev;
		i++;
	}
}

void	release_stack(t_stack *stack)
{
	t_node		*ptmp;
	t_node		*pdelete;
	t_node_info	*pdelete_info;
	int			i;

	ptmp = stack->head;
	i = 0;
	while (i < stack->size)
	{
		pdelete = ptmp;
		pdelete_info = ptmp->info;
		ptmp = ptmp->next;
		free(pdelete_info);
		free(pdelete);
		i++;
	}
	free(stack);
}

int	is_empty(t_stack *stack)
{
	if (stack->size == 0)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_init_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:31:57 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 13:35:32 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*init_stack(char name)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (stack == NULL)
		return (0);
	ft_memset(stack, 0, sizeof(t_stack));
	stack->stack_name = name;
	return (stack);
}

void	push(t_stack *stack, int num, int index)
{
	if (stack->size == 0)
		insert_at_first(stack, num, index);
	else
		insert_at_back(stack, num, index);
}

int	insert_at_first(t_stack *stack, int num, int index)
{
	t_node		*p_new_node;
	t_node_info	*p_new_node_info;

	p_new_node = malloc(sizeof(t_node));
	if (p_new_node == NULL)
		return (0);
	p_new_node_info = malloc(sizeof(t_node_info));
	if (p_new_node_info == NULL)
	{
		free(p_new_node);
		return (0);
	}
	ft_memset(p_new_node, 0, sizeof(t_node));
	ft_memset(p_new_node_info, 0, sizeof(t_node_info));
	p_new_node->info = p_new_node_info;
	p_new_node->content = num;
	p_new_node->index = index;
	stack->head = p_new_node;
	stack->tail = p_new_node;
	stack->size++;
	return (1);
}

int	insert_at_front(t_stack *stack, int num, int index)
{
	t_node		*p_new_node;
	t_node_info	*p_new_node_info;

	p_new_node = malloc(sizeof(t_node));
	if (p_new_node == NULL)
		return (0);
	p_new_node_info = malloc(sizeof(t_node_info));
	if (p_new_node_info == NULL)
	{
		free(p_new_node);
		return (0);
	}
	ft_memset(p_new_node, 0, sizeof(t_node));
	ft_memset(p_new_node_info, 0, sizeof(t_node_info));
	p_new_node->info = p_new_node_info;
	p_new_node->content = num;
	p_new_node->index = index;
	p_new_node->next = stack->head;
	p_new_node->prev = stack->tail;
	stack->head->prev = p_new_node;
	stack->tail->next = p_new_node;
	stack->head = p_new_node;
	stack->size++;
	return (1);
}

int	insert_at_back(t_stack *stack, int num, int index)
{
	t_node		*p_new_node;
	t_node_info	*p_new_node_info;

	p_new_node = malloc(sizeof(t_node));
	if (p_new_node == NULL)
		return (0);
	p_new_node_info = malloc(sizeof(t_node_info));
	if (p_new_node_info == NULL)
	{
		free(p_new_node);
		return (0);
	}
	ft_memset(p_new_node, 0, sizeof(t_node));
	ft_memset(p_new_node_info, 0, sizeof(t_node_info));
	p_new_node->info = p_new_node_info;
	p_new_node->content = num;
	p_new_node->index = index;
	p_new_node->next = stack->head;
	p_new_node->prev = stack->tail;
	stack->tail->next = p_new_node;
	stack->head->prev = p_new_node;
	stack->tail = p_new_node;
	stack->size++;
	return (1);
}

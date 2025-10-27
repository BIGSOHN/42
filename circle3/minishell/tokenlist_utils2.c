/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:17:36 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:23:46 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_token_node(t_tok_list *tok_list, int token_type)
{
	t_token	*ptmp;

	ptmp = find_token_node(tok_list, token_type);
	if (ptmp != NULL)
	{
		replace_token_pointer(tok_list, ptmp);
		tok_list->size--;
	}
}

void	delete_specific_node(t_tok_list *tok_list, t_token *delete_node)
{
	replace_token_pointer(tok_list, delete_node);
	tok_list->size--;
}

void	replace_token_pointer(t_tok_list *tok_list, t_token *ptoken)
{
	if (tok_list->size == 1)
		ft_memset(tok_list, 0, sizeof(tok_list));
	else if (ptoken == tok_list->head)
	{
		ptoken->next->prev = NULL;
		tok_list->head = ptoken->next;
	}
	else if (ptoken == tok_list->tail)
	{
		ptoken->prev->next = NULL;
		tok_list->tail = ptoken->prev;
	}
	else
	{
		ptoken->next->prev = ptoken->prev;
		ptoken->prev->next = ptoken->next;
	}
}

t_token	*find_token_node(t_tok_list *tok_list, int token_type)
{
	t_token	*ptmp;
	int		i;

	i = 0;
	ptmp = tok_list->head;
	while (i < tok_list->size)
	{
		if (ptmp->token_type == token_type)
			return (ptmp);
		ptmp = ptmp->next;
		i++;
	}
	return (0);
}

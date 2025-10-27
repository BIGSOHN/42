/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenlist_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:25:31 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:36:58 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_list	*init_tokenlist(void)
{
	t_tok_list	*tok_list;

	tok_list = ft_malloc(sizeof(t_tok_list));
	if (tok_list == NULL)
		exit(1);
	ft_memset(tok_list, 0, sizeof(t_tok_list));
	return (tok_list);
}

void	tok_insert_at_first(t_tok_list *tok_list, char *str, int token_type)
{
	t_token	*p_new_token;

	p_new_token = ft_malloc(sizeof(t_token));
	if (p_new_token == NULL)
		exit(1);
	ft_memset(p_new_token, 0, sizeof(t_token));
	p_new_token->str = str;
	p_new_token->token_type = token_type;
	tok_list->head = p_new_token;
	tok_list->tail = p_new_token;
	tok_list->size++;
}

void	tok_insert_at_back(t_tok_list *tok_list, char *str, int token_type)
{
	t_token	*p_new_token;

	p_new_token = ft_malloc(sizeof(t_token));
	if (p_new_token == NULL)
		exit(1);
	ft_memset(p_new_token, 0, sizeof(t_token));
	p_new_token->str = str;
	p_new_token->token_type = token_type;
	p_new_token->prev = tok_list->tail;
	tok_list->tail->next = p_new_token;
	tok_list->tail = p_new_token;
	tok_list->size++;
}

void	release_tokenlist(t_tok_list *tok_list)
{
	t_token	*ptmp;
	t_token	*pdelete;
	int		i;

	i = 0;
	ptmp = tok_list->head;
	while (i < tok_list->size)
	{
		pdelete = ptmp;
		ptmp = ptmp->next;
		free(pdelete->str);
		free(pdelete);
		i++;
	}
	free(tok_list);
}

void	print_tokenlist(t_tok_list *tok_list)
{
	t_token	*ptmp;
	int		i;

	i = 0;
	ptmp = tok_list->head;
	while (i < tok_list->size)
	{
		ptmp = ptmp->next;
		i++;
	}
}

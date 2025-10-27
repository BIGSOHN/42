/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_tokenlist_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:08:50 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/12 16:36:11 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dbl_list	*init_dbl_tokenlist(void)
{
	t_dbl_list	*dbl_toklist;

	dbl_toklist = ft_malloc(sizeof(t_dbl_list));
	if (dbl_toklist == NULL)
		exit(1);
	ft_memset(dbl_toklist, 0, sizeof(t_dbl_list));
	return (dbl_toklist);
}

void	push_dbl_token(t_dbl_list *dbl_list, char **strs, int tk_type, int wc)
{
	if (tk_type == INPUT_REDIRECTION
		|| tk_type == OUTPUT_REDIRECTION
		|| tk_type == HERE_DOCUMENT
		|| tk_type == APPEND_REDIRECTION)
		tk_type = LITERAL;
	if (dbl_list->size == 0)
		dbl_insert_fst(dbl_list, strs, tk_type, wc);
	else
		dbl_insert_back(dbl_list, strs, tk_type, wc);
}

void	dbl_insert_fst(t_dbl_list *dbl_list, char **strs, int tk_type, int wc)
{
	t_dbl_token	*p_new_token;

	p_new_token = ft_malloc(sizeof(t_dbl_token));
	if (p_new_token == NULL)
		exit(1);
	ft_memset(p_new_token, 0, sizeof(t_dbl_token));
	p_new_token->strs = strs;
	p_new_token->token_type = tk_type;
	p_new_token->word_count = wc;
	dbl_list->head = p_new_token;
	dbl_list->tail = p_new_token;
	dbl_list->size++;
}

void	dbl_insert_back(t_dbl_list *dbl_list, char **strs, int tk_type, int wc)
{
	t_dbl_token	*p_new_token;

	p_new_token = ft_malloc(sizeof(t_dbl_token));
	if (p_new_token == NULL)
		exit(1);
	ft_memset(p_new_token, 0, sizeof(t_dbl_token));
	p_new_token->strs = strs;
	p_new_token->token_type = tk_type;
	p_new_token->word_count = wc;
	p_new_token->prev = dbl_list->tail;
	dbl_list->tail->next = p_new_token;
	dbl_list->tail = p_new_token;
	dbl_list->size++;
}

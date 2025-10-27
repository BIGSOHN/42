/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:22:21 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:33:39 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_token_to_list(t_tok_list *tok_list, char *str, int token_type)
{
	if (tok_list->size == 0)
		tok_insert_at_first(tok_list, str, token_type);
	else
		tok_insert_at_back(tok_list, str, token_type);
}

void	fill_literal_token(t_tok_list *tok_list, char *str, int token_type)
{
	if (str != NULL)
		push_token(tok_list, str, token_type);
}

int	fill_delim_token(t_tok_list *tok_list, char *rdline, char *rd_str)
{
	int		delim_len;
	char	fst_delim;

	delim_len = 0;
	fst_delim = rd_str[0];
	if (fst_delim == '<' || fst_delim == '>')
		delim_len = redirection_token(tok_list, fst_delim, rdline);
	if (fst_delim == '|' || fst_delim == '&')
		delim_len = logic_pipe_token(tok_list, fst_delim, rdline);
	if (fst_delim == '\'')
		delim_len = single_quote_token(tok_list, fst_delim, rdline);
	if (fst_delim == '\"')
		delim_len = double_quote_token(tok_list, fst_delim, rdline);
	if (fst_delim == '(' || fst_delim == ')')
		delim_len = parenthesis_token(tok_list, fst_delim);
	if (fst_delim == ' ' || fst_delim == '\t')
		delim_len = white_space_token(tok_list, fst_delim);
	if (fst_delim == '$')
		delim_len = envp_key_token(tok_list, fst_delim, rdline);
	return (delim_len);
}

void	push_token(t_tok_list *tok_list, char *str, int token_flag)
{
	int	token_type;

	token_type = notice_token_type(str, token_flag);
	push_token_to_list(tok_list, str, token_type);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_token_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:23:58 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/24 22:02:41 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_continuous_token(t_tok_list *token_list)
{
	while (find_continuous_token(token_list, LITERAL) != NULL)
	{
		join_same_token(token_list, LITERAL);
	}
}

t_token	*find_continuous_token(t_tok_list *token_list, int token_type)
{
	t_token	*ptmp;
	int		i;

	i = 0;
	ptmp = token_list->head;
	while (i < token_list->size)
	{
		if (ptmp->next != NULL)
			if (ptmp->token_type == token_type
				&& ptmp->next->token_type == token_type)
				return (ptmp);
		ptmp = ptmp->next;
		i++;
	}
	return (NULL);
}

void	join_same_token(t_tok_list *token_list, int token_type)
{
	t_token	*first_token;
	t_token	*second_token;
	char	*join_str;

	first_token = find_continuous_token(token_list, token_type);
	second_token = NULL;
	if (first_token != NULL)
	{
		second_token = first_token->next;
		join_str = ft_strjoin(first_token->str, second_token->str);
		delete_specific_node(token_list, second_token);
		first_token->str = join_str;
	}
}

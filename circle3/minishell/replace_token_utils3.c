/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_token_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:18:20 by ssohn             #+#    #+#             */
/*   Updated: 2024/11/22 12:45:33 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_token_type_to_literal(t_tok_list *token_list)
{
	int		i;
	t_token	*ptmp;

	i = 0;
	ptmp = token_list->head;
	while (i < token_list->size)
	{
		if (ptmp->token_type == WORD)
			ptmp->token_type = LITERAL;
		if (ptmp->token_type == ENVP_KEY)
			ptmp->token_type = LITERAL;
		ptmp = ptmp->next;
		i++;
	}
}

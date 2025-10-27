/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_tokenlist_utils4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:18:08 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/15 14:37:09 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_before_delim(t_token *ptk)
{
	int	count;

	count = 0;
	while (ptk != NULL)
	{
		if (ptk->token_type == PIPE || ptk->token_type == LOGICAL_AND
			|| ptk->token_type == LOGICAL_OR
			|| ptk->token_type == OPEN_PARENTHESIS)
			break ;
		else
			count++;
		ptk = ptk->next;
	}
	return (count);
}

int	count_redir_before_delim(t_token *ptk)
{
	int	count;

	count = 0;
	if (ptk->token_type != OPEN_PARENTHESIS)
	{
		while (ptk != NULL)
		{
			if (ptk->token_type == PIPE || ptk->token_type == LOGICAL_AND
				|| ptk->token_type == LOGICAL_OR
				|| ptk->token_type == OPEN_PARENTHESIS)
				break ;
			else
			{
				if (is_redirection_token(ptk))
					count++;
			}
			ptk = ptk->next;
		}
	}
	return (count * 2);
}

int	count_continuous_token(t_token *ptk)
{
	int		count;
	int		token_type;
	t_token	*ptmp;

	count = 0;
	token_type = ptk->token_type;
	ptmp = ptk;
	while (ptmp != NULL)
	{
		if (ptmp->token_type == token_type)
			count++;
		else
			break ;
		ptmp = ptmp->next;
	}
	return (count);
}

int	count_covered_parenthesis_token(t_token *ptk)
{
	int		open_count;
	int		count;
	t_token	*ptmp;

	ptmp = ptk;
	open_count = 0;
	count = 0;
	while (ptmp->str != NULL)
	{
		if (ptmp->token_type == OPEN_PARENTHESIS)
			open_count++;
		if (ptmp->token_type == CLOSE_PARENTHESIS)
			open_count--;
		count++;
		if (ptmp->token_type == CLOSE_PARENTHESIS && open_count == 0)
			break ;
		ptmp = ptmp->next;
	}
	return (count);
}

int	count_null_before_delim(t_token *ptk)
{
	int	count;

	count = 0;
	while (ptk != NULL)
	{
		if (ptk->token_type == PIPE || ptk->token_type == LOGICAL_AND
			|| ptk->token_type == LOGICAL_OR
			|| ptk->token_type == OPEN_PARENTHESIS)
			break ;
		else
		{
			if (ptk->str == NULL)
				count++;
		}
		ptk = ptk->next;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:31:36 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:40:28 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_restricted_token_type(t_tok_type type)
{
	return (type == LOGICAL_AND
		|| type == LOGICAL_OR
		|| type == OPEN_PARENTHESIS
		|| type == CLOSE_PARENTHESIS
		|| type == BACKGROUND);
}

int	check_restricted_tokens(t_token *tok, t_sh_ctx *ctx)
{
	t_token			*current;
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	current = tok;
	while (current)
	{
		if (is_restricted_token_type(current->token_type))
		{
			set_temp_error(&temp, current->str, ERR_INVALID_SEQUENCE);
			apply_error(ctx, &temp);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	lexer(t_token *tok, t_sh_ctx *ctx)
{
	if (!tok)
		return (-1);
	if (check_restricted_tokens(tok, ctx) == -1)
	{
		print_syntax_error(ctx);
		return (-1);
	}
	if (command(tok, ctx) == 0)
		return (0);
	print_syntax_error(ctx);
	return (-1);
}

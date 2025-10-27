/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:03 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 13:57:18 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_file_token(t_token *file_token, t_token *curr \
	, t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (!file_token || is_redirection(file_token->str))
	{
		set_temp_error(temp, curr->str, ERR_INVALID_SEQUENCE);
		apply_error(ctx, temp);
		return (-1);
	}
	if ((file_token->token_type != WORD && file_token->token_type != LITERAL)
		|| filename(file_token, ctx) != 0)
	{
		set_temp_error(temp, curr->str, ERR_INVALID_SEQUENCE);
		apply_error(ctx, temp);
		return (-1);
	}
	return (0);
}

int	check_redirection_syntax(t_token *curr, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	t_token			*file_token;

	init_temp_error(&temp);
	if (curr && is_redirection(curr->str))
	{
		if (!curr->next)
		{
			set_temp_error(&temp, curr->str, ERR_INVALID_SEQUENCE);
			apply_error(ctx, &temp);
			return (-1);
		}
		file_token = curr->next;
		while (file_token && file_token->token_type == WHITE_SPACE)
			file_token = file_token->next;
		return (validate_file_token(file_token, curr, ctx, &temp));
	}
	return (0);
}

int	redirection(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok->next)
	{
		set_temp_error(&temp, tok->str, ERR_INVALID_SEQUENCE);
		apply_error(ctx, &temp);
		return (-1);
	}
	if (check_redirection_sequence(tok, &temp) == -1)
	{
		apply_error(ctx, &temp);
		return (-1);
	}
	return (0);
}

int	redirection_list(t_token *tok, t_sh_ctx *ctx)
{
	t_token	*current;

	if (!tok)
		return (-1);
	current = tok;
	while (current)
	{
		if (is_redirection(current->str))
		{
			if (check_redirection_syntax(current, ctx) == -1)
				return (-1);
			if (current->next)
				current = current->next;
		}
		else
			current = current->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:04:21 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:41:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection_error(t_token *tok, t_sh_ctx *ctx, t_syntax_error *temp)
{
	set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
	apply_error(ctx, temp);
	return (-1);
}

t_token	*find_file_token(t_token *curr)
{
	t_token	*file_token;

	file_token = curr->next;
	while (file_token && file_token->token_type == WHITE_SPACE)
		file_token = file_token->next;
	return (file_token);
}

int	validate_file_token(t_token *file_token \
	, t_token *curr, t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (!file_token)
		return (handle_redirection_error(curr, ctx, temp));
	if (is_redirection(file_token->str))
		return (handle_redirection_error(curr, ctx, temp));
	if (file_token->token_type != WORD && file_token->token_type != LITERAL)
		return (handle_redirection_error(curr, ctx, temp));
	if (filename(file_token, ctx) != 0)
		return (handle_redirection_error(curr, ctx, temp));
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
			return (handle_redirection_error(curr, ctx, &temp));
		file_token = find_file_token(curr);
		if (validate_file_token(file_token, curr, ctx, &temp) != 0)
			return (-1);
	}
	return (0);
}

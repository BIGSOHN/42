/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:00 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:42:07 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(t_token *tok, t_sh_ctx *ctx \
	, t_syntax_error *temp, int print_err)
{
	set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
	apply_error(ctx, temp);
	if (print_err)
		print_syntax_error(ctx);
	return (-1);
}

int	is_logical_operator(t_token *tok)
{
	if (tok->token_type != LOGICAL_AND
		&& tok->token_type != LOGICAL_OR
		&& tok->token_type != BACKGROUND)
		return (0);
	return (1);
}

int	compound_list(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	if (pipeline_command(tok, ctx))
		return (handle_error(tok, ctx, &temp, 0));
	while (tok && tok->next)
	{
		tok = tok->next;
		if (!is_logical_operator(tok))
			break ;
		if (!tok->next)
			return (handle_error(tok, ctx, &temp, 1));
		tok = tok->next;
		if (pipeline_command(tok, ctx))
			return (handle_error(tok, ctx, &temp, 1));
	}
	return (0);
}

int	pipeline_command(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	if (pipeline(tok, ctx))
	{
		set_temp_error(&temp, tok->str, ERR_INVALID_SEQUENCE);
		apply_error(ctx, &temp);
		return (-1);
	}
	return (0);
}

int	compound_command(t_token *tok, t_sh_ctx *ctx)
{
	t_token			*saved_tok;
	t_syntax_error	temp;

	init_temp_error(&temp);
	saved_tok = tok;
	if (!pipeline_command(tok, ctx))
		return (0);
	tok = saved_tok;
	if (!simple_command(tok, ctx))
		return (0);
	set_temp_error(&temp, tok->str, ERR_INVALID_SEQUENCE);
	apply_error(ctx, &temp);
	return (-1);
}

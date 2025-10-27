/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:00 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:41:55 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	t_token			*current;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	if (is_pipe(tok->str))
		return (handle_pipe_error(tok, ctx, &temp, ERR_INVALID_SEQUENCE));
	if (simple_command(tok, ctx) != 0)
	{
		set_temp_error(&temp, tok->str, ERR_INVALID_WORD);
		apply_error(ctx, &temp);
		return (-1);
	}
	current = tok;
	while (current)
	{
		if (is_pipe(current->str)
			&& check_next_command(&current, ctx, &temp) != 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

int	check_initial_pipe_sequence(t_token *tok, t_syntax_error *temp)
{
	if (!tok)
		return (-1);
	if (is_pipe(tok->str))
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	return (0);
}

int	check_consecutive_pipes(t_token *tok, t_syntax_error *temp)
{
	t_token	*current;

	current = tok;
	while (current && current->next)
	{
		if (is_pipe(current->str) && is_pipe(current->next->str))
		{
			set_temp_error(temp, current->next->str, ERR_CONSECUTIVE_OPERATOR);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	check_compound_sequence(t_token *tok, t_syntax_error *temp, t_sh_ctx *ctx)
{
	(void)ctx;
	if (!tok->next)
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (0);
	}
	tok = tok->next;
	if (tok->token_type == LOGICAL_AND
		|| tok->token_type == LOGICAL_OR
		|| tok->token_type == BACKGROUND)
	{
		set_temp_error(temp, tok->str, ERR_CONSECUTIVE_OPERATOR);
		return (0);
	}
	return (1);
}

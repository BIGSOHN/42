/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:03:00 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:41:49 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipeline_sequence(t_token *tok, t_syntax_error *temp, t_sh_ctx *ctx)
{
	if (!tok->next)
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (0);
	}
	if (*tok->next->str == '|')
	{
		set_temp_error(temp, tok->next->str, ERR_CONSECUTIVE_OPERATOR);
		return (0);
	}
	tok = tok->next;
	if (simple_command(tok, ctx))
	{
		set_temp_error(temp, tok->str, ERR_INVALID_WORD);
		return (0);
	}
	return (1);
}

int	check_pipeline_validity(t_token *tok, t_syntax_error *temp)
{
	if (!tok)
		return (0);
	if (is_pipe(tok->str))
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	if (tok->next && is_pipe(tok->next->str))
	{
		set_temp_error(temp, tok->next->str, ERR_CONSECUTIVE_OPERATOR);
		return (-1);
	}
	return (0);
}

int	handle_pipe_error(t_token *tok, t_sh_ctx *ctx \
	, t_syntax_error *temp, int error_type)
{
	if (error_type == ERR_CONSECUTIVE_OPERATOR)
		set_temp_error(temp, tok->str, ERR_CONSECUTIVE_OPERATOR);
	else
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
	apply_error(ctx, temp);
	return (-1);
}

int	check_command(t_token *tok, t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (simple_command(tok, ctx) != 0)
	{
		set_temp_error(temp, tok->str, ERR_INVALID_WORD);
		apply_error(ctx, temp);
		return (-1);
	}
	return (0);
}

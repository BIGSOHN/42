/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:31:36 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 00:04:32 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_consecutive_operators(t_token *current, t_syntax_error *temp)
{
	if (is_pipe(current->str) && is_pipe(current->next->str))
	{
		set_temp_error(temp, current->next->str, ERR_CONSECUTIVE_OPERATOR);
		return (-1);
	}
	if (is_redirection(current->str) && is_redirection(current->next->str))
	{
		if (ft_strlen(current->str) == 1 && ft_strlen(current->next->str) == 1
			&& current->str[0] == current->next->str[0])
		{
			set_temp_error(temp, current->next->str, ERR_CONSECUTIVE_OPERATOR);
			return (-1);
		}
	}
	return (0);
}

int	check_invalid_operator(t_token *token, t_syntax_error *temp)
{
	if (!token)
	{
		set_temp_error(temp, NULL, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	if (!token->next && (is_pipe(token->str) || is_redirection(token->str)))
	{
		set_temp_error(temp, token->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	return (0);
}

int	check_token_sequence(t_token *tok, t_syntax_error *temp)
{
	t_token	*current;

	if (check_invalid_operator(tok, temp) == -1)
		return (-1);
	if (is_pipe(tok->str))
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	current = tok;
	while (current && current->next)
	{
		if (check_consecutive_operators(current, temp) == -1)
			return (-1);
		current = current->next;
	}
	if (current && (is_pipe(current->str) || is_redirection(current->str)))
	{
		set_temp_error(temp, current->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
	return (0);
}

int	check_initial_command(t_token *tok, t_syntax_error *temp)
{
	t_token	*current;

	if (!tok)
		return (-1);
	if (is_pipe(tok->str))
	{
		set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		return (-1);
	}
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

int	process_command_elements(t_token *current \
	, t_sh_ctx *ctx, t_syntax_error *temp)
{
	int	result;

	while (current)
	{
		result = simple_command_element(current, ctx);
		if (result == -1)
		{
			set_temp_error(temp, current->str, ERR_INVALID_SEQUENCE);
			apply_error(ctx, temp);
			return (-1);
		}
		current = current->next;
	}
	return (0);
}

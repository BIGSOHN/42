/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:37:52 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:45:50 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_next_valid_token(t_token *current)
{
	while (current && current->token_type == WHITE_SPACE)
		current = current->next;
	return (current);
}

int	process_export(t_token *tok, t_sh_ctx *ctx)
{
	t_token	*current;

	if (word(tok, ctx) != 0)
		return (-1);
	current = tok->next;
	while (current)
	{
		if (current->token_type == WHITE_SPACE)
		{
			current = current->next;
			continue ;
		}
		if (ft_strncmp(current->str, "=", 1) == 0)
		{
			current = current->next;
			continue ;
		}
		if (ft_strchr(current->str, '='))
		{
			if (check_assignment_syntax(current, ctx) != 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	assignment_word(t_token *tok, t_sh_ctx *ctx)
{
	if (ft_strncmp(tok->str, "export", 7) == 0)
		return (process_export(tok, ctx));
	return (check_assignment_syntax(tok, ctx));
}

int	simple_command_element(t_token *tok, t_sh_ctx *ctx)
{
	if (!tok)
		return (-1);
	if (tok->token_type == WHITE_SPACE)
		return (0);
	if (tok->token_type == PIPE)
		return (check_pipe_syntax(tok));
	if ((tok->str[0] == '"' || tok->str[0] == '\'')
		&& word(tok, ctx) == 0)
		return (0);
	if (assignment_word(tok, ctx) == 0)
		return (0);
	if (word(tok, ctx) == 0)
		return (0);
	if (redirection(tok, ctx) == 0)
		return (0);
	return (-1);
}

int	process_command_tokens(t_token *current, \
	t_sh_ctx *ctx, t_syntax_error *temp)
{
	int	has_valid_element;

	has_valid_element = 0;
	while (current)
	{
		if (current->token_type == WHITE_SPACE)
		{
			current = current->next;
			continue ;
		}
		if (simple_command_element(current, ctx) == 0)
			has_valid_element = 1;
		else
		{
			set_temp_error(temp, current->str, ERR_INVALID_SEQUENCE);
			apply_error(ctx, temp);
			return (-1);
		}
		current = current->next;
	}
	if (has_valid_element)
		return (0);
	return (-1);
}

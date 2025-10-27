/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_command4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:35:37 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:42:16 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_subshell_closing(t_token *tok, t_syntax_error *temp)
{
	if (!tok || *(tok->str) != ')')
	{	
		if (tok)
			set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
		else
			set_temp_error(temp, ")", ERR_INVALID_SEQUENCE);
		return (0);
	}
	return (1);
}

int	subshell(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				is_valid;

	init_temp_error(&temp);
	if (!tok || *(tok->str) != '(')
		return (-1);
	if (!tok->next)
	{
		set_temp_error(&temp, ")", ERR_INVALID_SEQUENCE);
		apply_error(ctx, &temp);
		return (-1);
	}
	if (compound_list(tok->next, ctx))
	{
		set_temp_error(&temp, tok->next->str, ERR_INVALID_SEQUENCE);
		apply_error(ctx, &temp);
		return (-1);
	}	
	is_valid = check_subshell_closing(tok, &temp);
	if (!is_valid)
	{
		apply_error(ctx, &temp);
		return (-1);
	}
	return (0);
}

int	shell_command(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	if (*tok->str == '(' && tok->next)
	{
		if (!compound_list(tok->next, ctx))
			return (0);
		if (tok && *tok->str == ')')
			return (0);
	}
	return (compound_command(tok, ctx));
}

int	check_next_command(t_token **current, t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (!(*current)->next)
		return (handle_pipe_error(*current, ctx, temp \
		, ERR_INVALID_SEQUENCE));
	if (is_pipe((*current)->next->str))
		return (handle_pipe_error((*current)->next, ctx, temp \
		, ERR_CONSECUTIVE_OPERATOR));
	*current = (*current)->next;
	if (simple_command(*current, ctx) != 0)
	{
		set_temp_error(temp, (*current)->str, ERR_INVALID_WORD);
		apply_error(ctx, temp);
		return (-1);
	}
	return (0);
}

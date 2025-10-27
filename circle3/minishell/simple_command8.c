/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:18 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:50:38 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_quoted_content(t_token *tok, t_sh_ctx *ctx)
{
	size_t			idx;
	t_syntax_error	temp;
	int				result;

	init_temp_error(&temp);
	idx = 0;
	result = 0;
	if (!*(tok->str))
		return (result);
	while (tok->str[idx])
	{
		if (letter(tok->str[idx])
			&& ft_isdigit(tok->str[idx])
			&& special_char(tok->str[idx])
			&& tok->str[idx] != ' '
			&& tok->str[idx] != '\'')
		{
			set_temp_error(&temp, tok->str + idx, ERR_INVALID_CHAR);
			result = -1;
		}
		idx++;
	}
	apply_error(ctx, &temp);
	return (result);
}

int	double_quoted_string(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				result;

	init_temp_error(&temp);
	result = -1;
	if (!tok)
		return (result);
	if (*(tok->str) != '\"')
		return (result);
	tok->str++;
	if (!double_quoted_content(tok, ctx))
		return (result);
	tok->str++;
	if (!tok || *(tok->str) != '\"')
		return (result);
	result = 0;
	return (result);
}

int	handle_quote_error(char *str, t_sh_ctx *ctx, t_syntax_error *temp)
{
	set_temp_error(temp, str, ERR_INVALID_SEQUENCE);
	apply_error(ctx, temp);
	return (-1);
}

int	literal(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	char			*str;
	char			quote_char;

	init_temp_error(&temp);
	if (!tok || !tok->str)
		return (-1);
	str = tok->str;
	quote_char = *str;
	if (quote_char != '"' && quote_char != '\'')
		return (-1);
	str++;
	while (*str && *str != quote_char)
		str++;
	if (!*str)
		return (handle_quote_error(tok->str, ctx, &temp));
	if (*(str + 1) != '\0')
		return (handle_quote_error(tok->str, ctx, &temp));
	return (0);
}

int	check_pipe_syntax(t_token *tok)
{
	t_token	*next;

	next = tok->next;
	while (next && next->token_type == WHITE_SPACE)
		next = next->next;
	if (!next || next->token_type == PIPE)
		return (-1);
	return (0);
}

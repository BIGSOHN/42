/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:15:19 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:22:55 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	filechar_no_dot(char c, t_sh_ctx *ctx)
{
	(void)ctx;
	if (letter(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	dollar(t_token *tok, t_sh_ctx *ctx)
{
	char			*s;
	t_syntax_error	temp;
	int				result;

	init_temp_error(&temp);
	s = tok->str;
	result = -1;
	if (*s == '$')
	{
		s++;
		if (*s && (letter(*s) || ft_isdigit(*s) || *s == '.'))
			result = 0;
		else
			set_temp_error(&temp, s, ERR_INVALID_DOLLAR);
	}
	apply_error(ctx, &temp);
	return (result);
}

int	check_word_validity(char *s, t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (!s || !*s)
	{
		set_temp_error(temp, s, ERR_INVALID_WORD);
		apply_error(ctx, temp);
		return (0);
	}
	if (*s == '<' || *s == '>' || *s == '|')
	{
		set_temp_error(temp, s, ERR_INVALID_WORD);
		apply_error(ctx, temp);
		return (0);
	}
	return (1);
}

int	regular_word(t_token *tok, t_sh_ctx *ctx)
{
	t_token			*saved_tok;
	char			*s;
	t_syntax_error	temp;

	init_temp_error(&temp);
	saved_tok = tok;
	s = tok->str;
	if (!dollar(tok, ctx))
		tok = saved_tok;
	else
		s++;
	return (check_word_validity(s, ctx, &temp));
}

int	word(t_token *tok, t_sh_ctx *ctx)
{
	t_token			*saved_tok;
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok || !tok->str)
	{
		set_temp_error(&temp, NULL, ERR_INVALID_WORD);
		apply_error(ctx, &temp);
		return (-1);
	}
	saved_tok = tok;
	if (special_path(tok, ctx) == 0)
		return (0);
	tok = saved_tok;
	if (literal(tok, ctx) == 0)
		return (0);
	tok = saved_tok;
	if (regular_word(tok, ctx))
		return (0);
	tok = saved_tok;
	if (filename(tok, ctx) == 0)
		return (0);
	set_temp_error(&temp, tok->str, ERR_INVALID_WORD);
	apply_error(ctx, &temp);
	return (-1);
}

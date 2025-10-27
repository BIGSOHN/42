/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:16:46 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/19 12:50:56 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_name_chars(char *str, t_syntax_error *temp)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i] && result)
	{
		if (!letter(str[i]) && !ft_isdigit(str[i]))
		{
			set_temp_error(temp, str + i, ERR_INVALID_CHAR);
			result = 0;
		}
		i++;
	}
	return (result);
}

int	check_quoted_content(char *str, char quote_char, t_syntax_error *temp)
{
	int	result;

	result = 1;
	if (*str != quote_char)
	{
		set_temp_error(temp, str, ERR_INVALID_SEQUENCE);
		result = 0;
	}
	return (result);
}

int	single_quoted_content(t_token *tok, t_sh_ctx *ctx)
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
			&& tok->str[idx] != '"')
		{
			set_temp_error(&temp, tok->str + idx, ERR_INVALID_CHAR);
			result = -1;
		}
		idx++;
	}
	apply_error(ctx, &temp);
	return (result);
}

int	single_quoted_string(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				result;

	init_temp_error(&temp);
	result = -1;
	if (!tok)
		return (result);
	if (*(tok->str) != '\'')
		return (result);
	tok->str++;
	if (!single_quoted_content(tok, ctx))
		return (result);
	tok->str++;
	if (!tok || *(tok->str) != '\'')
		return (result);
	result = 0;
	return (result);
}

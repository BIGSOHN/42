/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:21:10 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 16:58:41 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_value_token(t_token *value_token, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!value_token)
		return (0);
	if (value_token->token_type != WORD && value_token->token_type != LITERAL)
	{
		set_temp_error(&temp, value_token->str, ERR_INVALID_WORD);
		apply_error(ctx, &temp);
		return (-1);
	}
	return (0);
}

int	check_var_name(char *var_name, t_sh_ctx *ctx, t_syntax_error *temp)
{
	int	i;

	if (!ft_isalpha(*var_name) && *var_name != '_')
	{
		set_temp_error(temp, var_name, ERR_INVALID_WORD);
		apply_error(ctx, temp);
		return (-1);
	}
	i = 0;
	while (var_name[++i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
		{
			set_temp_error(temp, var_name, ERR_INVALID_WORD);
			apply_error(ctx, temp);
			return (-1);
		}
	}
	return (0);
}

int	check_assignment_syntax(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	t_token			*value_token;
	char			*equals_pos;
	char			*var_name;

	init_temp_error(&temp);
	if (!tok || !tok->str)
		return (-1);
	equals_pos = ft_strchr(tok->str, '=');
	if (equals_pos > tok->str && *(equals_pos - 1) == '!')
		return (-1);
	if (!equals_pos || equals_pos == tok->str)
		return (0);
	var_name = ft_substr(tok->str, 0, equals_pos - tok->str);
	if (!var_name || check_var_name(var_name, ctx, &temp) == -1)
		return (-1);
	value_token = tok->next;
	while (value_token && value_token->token_type == WHITE_SPACE)
		value_token = value_token->next;
	return (check_value_token(value_token, ctx));
}

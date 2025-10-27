/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:37:52 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/19 13:06:34 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	letter(char c)
{
	if (c == '-' || ft_isalpha(c))
		return (1);
	return (0);
}

int	special_char(char c)
{
	if ((33 <= c && c <= 47)
		|| (58 <= c && c <= 64)
		|| (91 <= c && c <= 96)
		|| (123 <= c && c <= 126))
		return (0);
	return (-1);
}

int	check_regular_extension(char **s, t_syntax_error *temp, t_sh_ctx *ctx)
{
	int	is_valid;

	is_valid = 1;
	while (**s && is_valid)
	{
		if (filechar_no_dot(**s, ctx))
		{
			set_temp_error(temp, *s, ERR_INVALID_EXTENSION);
			is_valid = 0;
		}
		(*s)++;
	}
	return (is_valid);
}

int	check_hidden_extension(char **s, t_syntax_error *temp, t_sh_ctx *ctx)
{
	int	is_valid;

	is_valid = 1;
	while (**s && is_valid)
	{
		if (filechar_no_dot(**s, ctx))
		{
			set_temp_error(temp, *s, ERR_INVALID_EXTENSION);
			is_valid = 0;
		}
		(*s)++;
	}
	return (is_valid);
}

int	process_hidden_name(char **s, t_syntax_error *temp, t_sh_ctx *ctx)
{
	int	is_valid;

	is_valid = 1;
	if (!namepart(s, ctx))
	{
		(*s)++;
		if (**s == '.')
		{
			(*s)++;
			is_valid = check_hidden_extension(s, temp, ctx);
		}
	}
	else
	{
		set_temp_error(temp, *s, ERR_INVALID_HIDDEN_FILE);
		is_valid = 0;
	}
	return (is_valid);
}

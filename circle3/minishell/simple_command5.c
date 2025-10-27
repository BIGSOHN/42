/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:13:47 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/19 13:01:25 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_namepart_chars(char *str, t_syntax_error *temp, t_sh_ctx *ctx)
{
	int	i;
	int	is_valid;

	i = 0;
	is_valid = 1;
	while (str[i] && is_valid)
	{
		if (filechar_no_dot(str[i], ctx))
		{
			if (str[i] == '.' && str[i + 1] == '.')
				set_temp_error(temp, str + i, ERR_CONSECUTIVE_DOTS);
			else
				set_temp_error(temp, str + i, ERR_INVALID_CHAR);
			is_valid = 0;
		}
		i++;
	}
	return (is_valid);
}

int	namepart(char **str, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				is_valid;

	init_temp_error(&temp);
	is_valid = 1;
	if (!filechar(**str, ctx))
	{
		(*str)++;
		is_valid = check_namepart_chars(*str, &temp, ctx);
	}
	apply_error(ctx, &temp);
	if (is_valid)
		return (0);
	return (-1);
}

int	check_no_dot_chars(char **s, t_syntax_error *temp, t_sh_ctx *ctx)
{
	int	is_valid;

	is_valid = 1;
	while (**s && is_valid)
	{
		if (filechar_no_dot(**s, ctx) == -1)
		{
			set_temp_error(temp, *s, ERR_INVALID_CHAR);
			is_valid = 0;
		}
		(*s)++;
	}
	return (is_valid);
}

int	namepart_no_dot(char **s, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				is_valid;

	init_temp_error(&temp);
	if (**s && !filechar_no_dot(**s, ctx))
	{
		set_temp_error(&temp, *s, ERR_INVALID_START);
		is_valid = 0;
	}
	else
		is_valid = 1;
	if (is_valid)
		is_valid = check_no_dot_chars(s, &temp, ctx);
	apply_error(ctx, &temp);
	if (is_valid)
		return (0);
	return (-1);
}

int	filechar(char c, t_sh_ctx *ctx)
{
	t_syntax_error	temp;
	int				is_valid;

	init_temp_error(&temp);
	is_valid = 1;
	if (!letter(c) && !ft_isdigit(c) && c != '.')
	{
		set_temp_error(&temp, &c, ERR_INVALID_CHAR);
		is_valid = 0;
	}
	apply_error(ctx, &temp);
	if (is_valid)
		return (-1);
	return (0);
}

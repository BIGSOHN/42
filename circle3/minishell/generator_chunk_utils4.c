/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_chunk_utils4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 23:43:49 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 00:22:08 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exception_len(char **s, t_sh_ctx *ctx, int *i)
{
	(void)ctx;
	if (!ft_strncmp("$\"", *s, 2))
	{
		*s += 1;
		while (**s && **s != '\"')
		{
			(*i)++;
			(*s)++;
		}
		return (0);
	}
	if (!ft_strncmp("$\'", *s, 2))
	{
		*s += 1;
		while (**s && **s != '\'')
		{
			(*i)++;
			(*s)++;
		}
		return (0);
	}
	return (-1);
}

int	special_command_len(char **s, t_sh_ctx *ctx, int *i)
{
	char	*tmp;
	int		*status;
	int		idx;

	status = get_exit_status();
	if ((!ft_strncmp(*s, "$?", 2)))
	{
		*s += 2;
		tmp = ft_itoa(*status);
		idx = ft_strlen(tmp);
		*i = idx;
		return (0);
	}
	if (!ft_strncmp(*s, "~", 1))
	{
		idx = ft_strlen(ctx->home_path);
		*i = idx;
		(*s)++;
		return (0);
	}
	return (-1);
}

void	handle_special_char_length(char **s, size_t *len, t_sh_ctx *ctx)
{
	if (**s == '$' || **s == '~')
		*len += env_to_len(s, ctx);
	else if (**s == '\'')
		*len += single_quote_strlen(s);
	else if (**s == '"')
		*len += double_quote_strlen(s, ctx);
}

int	check_string_length(char *s, t_sh_ctx *ctx)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == '$' || *s == '~' || *s == '\'' || *s == '"')
		{
			handle_special_char_length(&s, &len, ctx);
			continue ;
		}
		len++;
		s++;
	}
	return (len);
}

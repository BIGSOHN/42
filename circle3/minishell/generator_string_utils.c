/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_string_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:50:28 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/31 19:38:03 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_exception(char **s, char *chunk, t_sh_ctx *ctx, int *i)
{
	(void)ctx;
	if (!ft_strncmp("$\"", *s, 2))
	{
		*s += 1;
		while (**s && **s != '\"')
		{
			chunk[(*i)++] = **s;
			(*s)++;
		}
		return (0);
	}
	if (!ft_strncmp("$\'", *s, 2))
	{
		*s += 1;
		while (**s && **s != '\'')
		{
			chunk[(*i)++] = **s;
			(*s)++;
		}
		return (0);
	}
	return (-1);
}

int	handle_env_variable(char **s, char *chunk, t_sh_ctx *ctx)
{
	char	*key;
	char	*val;
	int		idx;

	idx = 1;
	while ((*s)[idx] && (ft_isalnum((*s)[idx]) || (*s)[idx] == '_'))
		idx++;
	key = ft_substr(*s, 1, idx - 1);
	val = ft_strdup(find_envp_value(ctx->env_list, key));
	*s += idx;
	if (!val)
		return (0);
	return (copy_env_value(chunk, val, ctx));
}

int	env_to_text(char **s, char *chunk, t_sh_ctx *ctx)
{
	int	i;

	i = 0;
	if (!handle_exception(s, chunk, ctx, &i))
		return (i);
	if (!is_special_command(s, chunk, ctx, &i))
		return (i);
	if (!(*s)[1] || (!ft_isalpha((*s)[1]) && (*s)[1] != '_'))
	{
		chunk[i++] = **s;
		(*s)++;
		return (i);
	}
	return (handle_env_variable(s, chunk, ctx));
}

int	process_single_quote(char **s, char *chunk)
{
	size_t	idx;

	idx = 0;
	(*s)++;
	while (**s != '\'')
	{
		*chunk++ = **s;
		(*s)++;
		idx++;
	}
	(*s)++;
	return (idx);
}

int	process_double_quote(char **s, char *chunk, t_sh_ctx *ctx)
{
	int	idx;

	idx = 0;
	(*s)++;
	while (**s && **s != '\"')
	{
		if (**s == '$')
			idx += env_to_text(s, chunk + idx, ctx);
		else
		{
			chunk[idx++] = **s;
			(*s)++;
		}
	}
	(*s)++;
	return (idx);
}

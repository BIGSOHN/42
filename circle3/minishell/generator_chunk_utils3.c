/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_chunk_utils3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:48:03 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 00:21:41 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_value_len(char *val)
{
	size_t	idx;
	int		i;

	i = 0;
	idx = 0;
	while (val[i] == ' ')
		i++;
	while (val[i] != '\0')
	{
		if (val[i] == ' ')
			i++;
		while (val[i] == ' ')
			i++;
		if (val[i] == '\0')
			continue ;
		idx++;
		i++;
	}
	return (i);
}

int	handle_env_variable_len(char **s, t_sh_ctx *ctx)
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
	return (get_value_len(val));
}

size_t	env_to_len(char **s, t_sh_ctx *ctx)
{
	int	i;

	i = 0;
	if (!handle_exception_len(s, ctx, &i))
		return (i);
	if (!special_command_len(s, ctx, &i))
		return (i);
	if (!(*s)[1] || (!ft_isalpha((*s)[1]) && (*s)[1] != '_'))
	{
		i++;
		(*s)++;
		return (i);
	}
	return (handle_env_variable_len(s, ctx));
}

size_t	single_quote_strlen(char **s)
{
	size_t	idx;

	idx = 0;
	(*s)++;
	while (**s != '\'')
	{
		(*s)++;
		idx++;
	}
	(*s)++;
	return (idx);
}

size_t	double_quote_strlen(char **s, t_sh_ctx *ctx)
{
	int	idx;

	idx = 0;
	(*s)++;
	while (**s && **s != '\"')
	{
		if (**s == '$')
			idx += env_to_len(s, ctx);
		else
		{
			idx++;
			(*s)++;
		}
	}
	(*s)++;
	return (idx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_chunk_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:48:03 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/31 19:32:07 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	resize_cmd_buffer(t_sh_ctx *ctx)
{
	char	**new_cmd;
	int		new_size;
	int		i;

	new_size = ctx->max_cmd * 2;
	new_cmd = ft_calloc(new_size, sizeof(char *));
	if (new_cmd == NULL)
		return (0);
	i = -1;
	while (++i < ctx->max_cmd)
	{
		new_cmd[i] = ctx->buf->cmd[i];
	}
	ctx->buf->cmd = new_cmd;
	ctx->max_cmd = new_size;
	return (1);
}

int	copy_env_value(char *chunk, char *val, t_sh_ctx *ctx)
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
		{
			separate_into_chunks(&chunk, ctx, &idx);
			ft_memset(chunk, 0, sizeof(char) * ft_strlen(chunk));
			i++;
		}
		while (val[i] == ' ')
			i++;
		if (val[i] == '\0')
			continue ;
		chunk[idx++] = val[i];
		i++;
	}
	return (i);
}

void	substitute_file_name(char *s, t_sh_ctx *ctx)
{
	char	*chunk;
	char	*init;
	size_t	idx;

	chunk = initialize(&idx, ctx, &init, s);
	while (*s)
	{
		if (*s == '$' || *s == '~' || *s == '\'' || *s == '"')
		{
			handle_special_char(&s, chunk, &idx, ctx);
			continue ;
		}
		else
			chunk[idx++] = *s;
		s++;
	}
	if (*init)
		ctx->buf->file_name = ft_strdup(chunk);
	else
		ctx->buf->file_name = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_chunk_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:48:03 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 00:27:25 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	separate_into_chunks(char **chunk, t_sh_ctx *ctx, size_t *idx)
{
	ctx->buf->idx++;
	if ((int)ctx->buf->idx > ctx->max_cmd - 2)
		resize_cmd_buffer(ctx);
	ctx->buf->cmd[ctx->buf->idx] = ft_strdup(*chunk);
	ft_memset(*chunk, 0, sizeof(char) * ft_strlen(*chunk));
	*idx = 0;
}

char	*initialize(size_t *idx, t_sh_ctx *ctx, char **init, char *s)
{
	char	*str;
	int		size;

	*idx = 0;
	size = check_string_length(s, ctx) + 1;
	str = ft_calloc(size, sizeof(char));
	if (str == NULL)
		exit(0);
	*init = str;
	return (str);
}

void	handle_special_char(char **s, char *chunk, size_t *idx, t_sh_ctx *ctx)
{
	if (**s == '$' || **s == '~')
		*idx += env_to_text(s, chunk + *idx, ctx);
	else if (**s == '\'')
		*idx += process_single_quote(s, chunk + *idx);
	else if (**s == '"')
		*idx += process_double_quote(s, chunk + *idx, ctx);
}

void	substitute_cmd_variable(char *s, t_sh_ctx *ctx)
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
		else if (*s == ' ')
			separate_into_chunks(&chunk, ctx, &idx);
		else
			chunk[idx++] = *s;
		s++;
	}
	if (*init)
		separate_into_chunks(&chunk, ctx, &idx);
}

void	strings_to_chunk(t_bt_node *node, t_sh_ctx *ctx)
{
	size_t	idx;
	t_redir	*init;

	idx = 0;
	ctx->buf->idx = -1;
	ft_memset(ctx->buf->cmd, 0, sizeof(char *) * ctx->max_cmd);
	while (node->cmd[idx])
	{
		substitute_cmd_variable(node->cmd[idx], ctx);
		idx++;
	}
	idx = 0;
	while (ctx->buf->cmd[idx])
		idx++;
	ctx->origin_cmd = ft_strdup(*(ctx->buf->cmd));
	node->cmd = ctx->buf->cmd;
	node->word_count = idx;
	init = node->redir;
	while (node->redir != NULL && node->redir->file_name != NULL)
	{
		substitute_file_name(node->redir->file_name, ctx);
		node->redir->file_name = ctx->buf->file_name;
		node->redir = node->redir->next;
	}
	node->redir = init;
}

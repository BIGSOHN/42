/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:57 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 00:26:25 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_double_quote_for_here_doc(char **s, char *chunk)
{
	int	idx;

	idx = 0;
	(*s)++;
	while (**s && **s != '\"')
	{
		chunk[idx++] = **s;
		(*s)++;
	}
	(*s)++;
	return (idx);
}

static	char	*initialize_limiter(size_t *idx, char **init, char *s)
{
	char	*str;
	int		size;

	*idx = 0;
	size = ft_strlen(s) + 1;
	str = ft_calloc(size, sizeof(char));
	if (str == NULL)
		exit(0);
	*init = str;
	return (str);
}

char	*preprocess_limiter(char *s)
{
	char	*chunk;
	char	*init;
	size_t	idx;

	chunk = initialize_limiter(&idx, &init, s);
	while (*s)
	{
		if (*s == '\'')
			idx += process_single_quote(&s, chunk + idx);
		else if (*s == '"')
			idx += process_double_quote_for_here_doc(&s, chunk + idx);
		else
			chunk[idx++] = *s++;
	}
	if (*init)
		return (ft_strdup(chunk));
	return (chunk);
}

int	handle_here_doc_exception(t_redir *redir, int fd, t_sh_ctx *ctx)
{
	if (g_flag == SIGINT)
		sigint_handle_exception(redir, fd, ctx);
	else
		null_handle_exception(redir, fd, ctx);
	postprocess_heredoc(fd, ctx);
	return (-1);
}

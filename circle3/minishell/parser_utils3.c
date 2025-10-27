/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:57 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/26 14:49:43 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *s, size_t *idx, t_sh_ctx *ctx)
{
	char	*value;
	char	*str;
	size_t	i;

	str = s;
	i = 1;
	while (ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))
		i++;
	value = find_envp_value(ctx->env_list, ft_substr(str, 1, i - 1));
	*idx += i;
	return (value);
}

char	*env_to_text_in_heredoc(char *s, t_sh_ctx *ctx)
{
	char	*chunk;
	size_t	idx;
	size_t	start;
	size_t	end;

	chunk = 0;
	start = 0;
	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '$')
		{
			if (start == 0)
			{
				end = idx;
				chunk = ft_substr(s, start, end);
				start = end + 1;
			}
			chunk = ft_strjoin(chunk, get_env_value(&s[idx], &idx, ctx));
			start = idx;
			continue ;
		}
		idx++;
	}
	return (ft_strjoin(chunk, ft_substr(s, start, idx)));
}

int	write_heredoc(t_redir *redir, t_sh_ctx *ctx)
{
	char	*line;
	char	*eof;
	int		fd;

	preprocess_heredoc(redir, ctx);
	fd = open(redir->file_name, O_WRONLY);
	redir->limiter = preprocess_limiter(redir->limiter);
	eof = ft_strjoin(redir->limiter, "\n");
	while (1)
	{
		write(STDOUT_FILENO, ">", 2);
		line = get_next_line(0);
		if (!line || g_flag == SIGINT)
		{
			handle_here_doc_exception(redir, fd, ctx);
			unlink(redir->file_name);
			return (0);
		}
		if (!ft_strncmp(line, eof, ft_strlen(eof) + 1))
			break ;
		line = env_to_text_in_heredoc(line, ctx);
		ft_putstr_fd(line, fd);
	}
	return (postprocess_heredoc(fd, ctx));
}

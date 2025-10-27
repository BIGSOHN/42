/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:57 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/02 14:13:32 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_operation(t_redir *redir, t_sh_ctx *ctx)
{
	int	is_incompleted;

	while (redir)
	{	
		is_incompleted = 0;
		if (!ft_strncmp(redir->redir_sign, "<<", 3))
		{
			if (!write_heredoc(redir, ctx))
			{
				unlink(redir->file_name);
				is_incompleted = 1;
				if (g_flag == SIGINT)
					break ;
			}
		}
		redir = redir->next;
	}
	return (is_incompleted);
}

int	check_here_doc(t_redir *redir, t_sh_ctx *ctx, int flag)
{
	if (flag == WRITE)
	{	
		if (ctx->origin_dir == NULL)
			ctx->origin_dir = redir;
		if (handle_heredoc_operation(redir, ctx))
			return (-1);
	}
	else if (flag == UNLINK)
	{
		while (redir)
		{
			if (!ft_strncmp(redir->redir_sign, "<<", 3) && redir->file_name)
			{
				unlink(redir->file_name);
			}
			redir = redir->next;
		}
	}
	return (0);
}

int	make_tmp_file(t_redir *redir, t_sh_ctx *ctx)
{
	char	*str;
	int		n;

	(void)ctx;
	n = 0;
	redir->limiter = redir->file_name;
	while (1)
	{
		str = ft_itoa(n);
		redir->file_name = ft_strjoin("./.temp", str);
		redir->fd = open(redir->file_name, O_WRONLY | O_EXCL | O_CREAT, 0644);
		if (redir->fd != -1)
		{
			close(redir->fd);
			return (-1);
		}
		n++;
	}
	return (0);
}

void	preprocess_heredoc(t_redir *redir, t_sh_ctx *ctx)
{
	set_here_doc_terminal_attr(ctx);
	if (!make_tmp_file(redir, ctx))
	{
		perror("can't make temporary file");
		return ;
	}
}

int	postprocess_heredoc(int fd, t_sh_ctx *ctx)
{
	(void)ctx;
	close(fd);
	return (1);
}

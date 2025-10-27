/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection_funcs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:19:37 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/29 14:09:14 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_heredoc_redir(t_redir *redir, t_sh_ctx *sh_ctx)
{
	int	*status;

	sh_ctx->is_stdin = false;
	if (sh_ctx->in_fd != -1)
	{
		close(sh_ctx->in_fd);
		sh_ctx->in_fd = -1;
	}
	sh_ctx->in_fd = open(redir->file_name, O_RDONLY);
	if (sh_ctx->in_fd == -1)
	{
		perror("heredoc open fail");
		status = get_exit_status();
		ft_lstclear(get_gc(), free);
		exit(*status);
	}
	sh_ctx->is_stdin = true;
}

void	exec_input_redir(t_redir *redir, t_sh_ctx *sh_ctx)
{	
	char	*tmp;

	if (sh_ctx->in_fd != -1)
	{
		close(sh_ctx->in_fd);
		sh_ctx->in_fd = -1;
	}
	tmp = redir->file_name;
	if (tmp == NULL)
		handle_exception_input_redir(redir, sh_ctx, tmp);
	sh_ctx->is_stdin = false;
	sh_ctx->in_fd = open(redir->file_name, O_RDWR, 0644);
	if (sh_ctx->in_fd == -1)
		handle_exception_input_redir(redir, sh_ctx, tmp);
	sh_ctx->is_stdin = true;
}

void	exec_output_redir(t_redir *redir, t_sh_ctx *sh_ctx)
{
	char	*tmp;

	if (sh_ctx->out_fd != -1)
	{
		close(sh_ctx->out_fd);
		sh_ctx->out_fd = -1;
	}
	tmp = redir->file_name;
	if (tmp == NULL)
		handle_exception_output_redir(redir, sh_ctx, tmp);
	sh_ctx->out_fd = \
	open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (sh_ctx->out_fd == -1)
		handle_exception_output_redir(redir, sh_ctx, tmp);
	sh_ctx->is_stdout = true;
}

void	exec_append_redir(t_redir *redir, t_sh_ctx *sh_ctx)
{
	char	*tmp;

	if (sh_ctx->out_fd != -1)
	{
		close(sh_ctx->out_fd);
		sh_ctx->out_fd = -1;
	}
	tmp = redir->file_name;
	if (tmp == NULL)
		handle_exception_output_redir(redir, sh_ctx, tmp);
	sh_ctx->out_fd = \
	open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (sh_ctx->out_fd == -1)
		handle_exception_output_redir(redir, sh_ctx, tmp);
	sh_ctx->is_stdout = true;
}

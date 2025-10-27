/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:48:44 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:13:57 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_redirection(t_bt_node *node, t_sh_ctx *ctx)
{
	struct s_redir	*copied_redir;

	copied_redir = node->redir;
	while (copied_redir)
	{
		if (!ft_strncmp(copied_redir->redir_sign, "<<", 3))
			exec_heredoc_redir(copied_redir, ctx);
		if (!ft_strncmp(copied_redir->redir_sign, "<", 2))
			exec_input_redir(copied_redir, ctx);
		if (!ft_strncmp(copied_redir->redir_sign, ">", 2))
			exec_output_redir(copied_redir, ctx);
		if (!ft_strncmp(copied_redir->redir_sign, ">>", 3))
			exec_append_redir(copied_redir, ctx);
		copied_redir = copied_redir->next;
	}
}

void	stdin_redirection(int *in, t_sh_ctx *ctx)
{
	*in = dup2(ctx->in_fd, STDIN_FILENO);
	if (*in == -1)
	{
		perror("stdin dup2 error");
		exit(1);
	}
	close(ctx->in_fd);
	ctx->in_fd = -1;
}

void	file_stdout_redirection(int *out, t_sh_ctx *ctx)
{
	if (ctx->pipe_groups[ctx->cur_group]->pipes[1] != -1)
		close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
	ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
	*out = dup2(ctx->out_fd, STDOUT_FILENO);
	if (*out == -1)
	{
		perror("stdin dup2 error");
		exit(1);
	}
	close(ctx->out_fd);
	ctx->out_fd = -1;
	ctx->is_stdout = false;
}

void	stdout_redirection(int *out, t_sh_ctx *ctx)
{
	*out = dup2(ctx->pipe_groups[ctx->cur_group]->pipes[1], STDOUT_FILENO);
	if (*out == -1)
	{
		perror("stdin dup2 error");
		exit(1);
	}
	close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
	ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
}

void	pipe_redirection(t_bt_node *cur_node, t_sh_ctx *ctx)
{
	int	in;
	int	out;

	in = 0;
	out = 0;
	if (ctx->pipe_groups[ctx->cur_group]->pipes[0] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
		ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
	}
	if (ctx->in_fd != -1)
		stdin_redirection(&in, ctx);
	if (ctx->is_stdout)
		file_stdout_redirection(&out, ctx);
	else
	{
		if (ctx->pipe_groups[ctx->cur_group]->cur_cmd
			<= ctx->pipe_groups[ctx->cur_group]->cmd_count - 1)
			stdout_redirection(&out, ctx);
	}
	if (cur_node->redir != NULL)
		check_here_doc(cur_node->redir, ctx, UNLINK);
}

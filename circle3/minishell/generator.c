/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:47:04 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/02 13:50:38 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_sh_ctx *ctx)
{
	t_bt_node		*root;

	root = *ctx->ast_info->root;
	if (!initialize_exec(ctx))
		return (0);
	exec_in_order(root, ctx);
	if (ctx->is_fork)
	{
		if (!postprocess(ctx))
			return (1);
	}
	return (1);
}

void	parent_pipe_redirection(t_sh_ctx *ctx)
{
	if (ctx->in_fd != -1)
	{
		close(ctx->in_fd);
		ctx->in_fd = -1;
	}
	close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
	ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
	ctx->in_fd = dup(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
	if (ctx->in_fd == -1)
	{
		perror("dup error");
		exit(1);
	}
	close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
	ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
}

void	exec_other_command(t_bt_node *node, t_sh_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		handle_fork_exception(ctx);
	else if (pid == 0)
	{
		set_chlid_signal_attr();
		if (node->redir)
			file_redirection(node, ctx);
		pipe_redirection(node, ctx);
		check_and_execute(node, ctx);
	}
	else if (pid > 0)
	{
		ctx->pid_table.pids[(ctx->pid_table.idx)++] = pid;
		ctx->is_fork = true;
		set_parent_term_attr();
		if (ctx->pipe_groups[ctx->cur_group]->cur_cmd
			<= ctx->pipe_groups[ctx->cur_group]->cmd_count - 1)
			parent_pipe_redirection(ctx);
		else
			close_pipe_redirection(ctx);
	}
}

int	exec_chlid_process(t_bt_node *node, t_sh_ctx *ctx)
{
	int	idx;
	int	count;

	idx = ctx->pipe_groups[ctx->cur_group]->pipe_idx;
	count = ctx->pipe_groups[ctx->cur_group]->pipe_count;
	ctx->pipe_groups[ctx->cur_group]->cur_cmd++;
	if (idx < count && pipe(ctx->pipe_groups[ctx->cur_group]->pipes) < 0)
	{
		perror("pipe error");
		close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
		close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
		exit(EXIT_FAILURE);
	}
	ctx->pipe_groups[ctx->cur_group]->pipe_idx++;
	exec_other_command(node, ctx);
	return (0);
}

int	exec_in_order(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	if (!node)
		return (-1);
	exec_in_order(node->left, sh_ctx);
	if (node->type == LOGICAL_AND || node->type == LOGICAL_OR)
	{
		if (preprocess_logical_operator(node, sh_ctx))
			return (0);
	}
	if (node->type == OPEN_PARENTHESIS)
		exec_subshell(node, sh_ctx);
	if (node->type == LITERAL)
	{
		strings_to_chunk(node, sh_ctx);
		if (sh_ctx->pipe_groups[sh_ctx->cur_group]->cmd_count == 1
			&& !execute_builtin_parent(node, sh_ctx))
			return (0);
		exec_chlid_process(node, sh_ctx);
	}
	if (node->right != NULL)
		exec_in_order(node->right, sh_ctx);
	return (0);
}

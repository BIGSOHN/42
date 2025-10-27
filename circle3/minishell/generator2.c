/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:47:04 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 00:29:16 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fork_exception(t_sh_ctx *ctx)
{
	perror("fork failed");
	close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
	close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
	exit(EXIT_FAILURE);
}

void	restore_redir_fd(t_sh_ctx *ctx)
{
	if (ctx->in_fd != -1)
	{
		close(ctx->in_fd);
		ctx->in_fd = -1;
	}
	if (ctx->out_fd != -1)
	{
		close(ctx->out_fd);
		ctx->out_fd = -1;
	}
}

void	restore_fd(t_sh_ctx *ctx)
{
	int	in;

	close(STDIN_FILENO);
	in = dup2(ctx->backup_fd.stdin, STDIN_FILENO);
	if (in == -1)
	{
		perror("stdin dup2 error");
		exit(1);
	}
	close(ctx->backup_fd.stdin);
	ctx->backup_fd.stdin = -1;
	close(STDOUT_FILENO);
	in = dup2(ctx->backup_fd.stdout, STDOUT_FILENO);
	if (in == -1)
	{
		perror("stdout dup2 error");
		exit(1);
	}
	close(ctx->backup_fd.stdout);
	ctx->backup_fd.stdout = -1;
	restore_redir_fd(ctx);
}

void	set_chlid_signal_attr(void)
{
	struct sigaction	sa_child_quit;
	struct sigaction	sa_child_int;

	sa_child_int.sa_handler = SIG_DFL;
	sigemptyset(&sa_child_int.sa_mask);
	sa_child_int.sa_flags = 0;
	sigaction(SIGINT, &sa_child_int, NULL);
	sa_child_quit.sa_handler = SIG_DFL;
	sigemptyset(&sa_child_quit.sa_mask);
	sa_child_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_child_quit, NULL);
}

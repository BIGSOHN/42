/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection_funcs_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:19:37 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/29 14:37:23 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	print_input_error_msg(t_redir *redir, t_sh_ctx *ctx, char *tmp)
{
	(void)ctx;
	if (errno == EACCES)
		ft_putstr_fd(ft_strjoin(redir->origin_file_name, \
		": Permission denied\n"), 2);
	if (tmp == NULL)
		ft_putstr_fd(ft_strjoin(redir->origin_file_name, \
		": ambiguous redirect\n"), 2);
	else
		ft_putstr_fd(ft_strjoin(tmp, \
		": No such file or directory\n"), 2);
}

void	handle_exception_input_redir(t_redir *redir, t_sh_ctx *ctx, char *tmp)
{	
	int		*status;

	ft_putstr_fd("minishell : ", 2);
	print_input_error_msg(redir, ctx, tmp);
	if (ctx->pipe_groups[ctx->cur_group]->pipes[0] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
		ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
	}
	if (ctx->pipe_groups[ctx->cur_group]->pipes[1] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
		ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
	}
	if (ctx->in_fd != -1)
	{
		close(ctx->in_fd);
		ctx->in_fd = -1;
	}
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	status = get_exit_status();
	*status = truncate_8bits("1");
	exit(*status);
}

void	print_output_error_msg(t_redir *redir, t_sh_ctx *ctx, char *tmp)
{
	(void)ctx;
	if (errno == EACCES)
		ft_putstr_fd(ft_strjoin(redir->origin_file_name, \
		": Permission denied\n"), 2);
	if (tmp == NULL || tmp[0] == '\0')
	{
		ft_putstr_fd(ft_strjoin(redir->origin_file_name, \
		": ambiguous redirect\n"), 2);
	}
}

void	init_pipe_fd(t_sh_ctx *ctx)
{
	if (ctx->pipe_groups[ctx->cur_group]->pipes[0] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
		ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
	}
	if (ctx->pipe_groups[ctx->cur_group]->pipes[1] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
		ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
	}
}

void	handle_exception_output_redir(t_redir *redir, t_sh_ctx *ctx, char *tmp)
{	
	int		*status;

	ft_putstr_fd("minishell : ", 2);
	print_output_error_msg(redir, ctx, tmp);
	init_pipe_fd(ctx);
	if (ctx->out_fd != -1)
	{
		close(ctx->out_fd);
		ctx->out_fd = -1;
	}
	check_here_doc(ctx->origin_dir, ctx, UNLINK);
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	status = get_exit_status();
	*status = truncate_8bits("1");
	exit(*status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_redirection2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:48:44 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/15 17:02:17 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_redirection(t_sh_ctx *ctx)
{
	if (ctx->in_fd != -1)
	{
		close(ctx->in_fd);
		ctx->in_fd = -1;
	}
	if (ctx->pipe_groups[ctx->cur_group]->pipes[1] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[1]);
		ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
	}	
	if (ctx->pipe_groups[ctx->cur_group]->pipes[0] != -1)
	{
		close(ctx->pipe_groups[ctx->cur_group]->pipes[0]);
		ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
	}
}

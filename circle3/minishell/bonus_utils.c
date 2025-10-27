/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:16:08 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 13:47:40 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preprocess_logical_operator(t_bt_node *node, t_sh_ctx *ctx)
{	
	if (!ft_strncmp(*node->cmd, "&&", 3))
	{
		if (!ctx->pipe_groups[ctx->cur_group]->exit_status)
			return (0);
	}
	if (!ft_strncmp(*node->cmd, "||", 3))
	{
		if (!ctx->pipe_groups[ctx->cur_group]->exit_status)
			return (0);
	}
	return (1);
}

int	exec_subshell(t_bt_node *node, t_sh_ctx *sh_ctx)
{	
	(void)node;
	(void)sh_ctx;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_func_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:30 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/15 17:40:41 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_cmd(t_sh_ctx *sh_ctx)
{
	sh_ctx->child_bulitin_funcs[0] = "echo";
	sh_ctx->child_bulitin_funcs[1] = "env";
	sh_ctx->child_bulitin_funcs[2] = "pwd";
	sh_ctx->child_bulitin_funcs[3] = NULL;
	sh_ctx->parent_bulitin_funcs[0] = "cd";
	sh_ctx->parent_bulitin_funcs[1] = "export";
	sh_ctx->parent_bulitin_funcs[2] = "unset";
	sh_ctx->parent_bulitin_funcs[3] = "exit";
	sh_ctx->parent_bulitin_funcs[4] = NULL;
}

void	init_shell_funcs(t_sh_ctx *sh_ctx)
{
	sh_ctx->parent_bulitin_func[0] = ft_cd;
	sh_ctx->parent_bulitin_func[1] = ft_export;
	sh_ctx->parent_bulitin_func[2] = ft_unset;
	sh_ctx->parent_bulitin_func[3] = ft_exit;
	sh_ctx->parent_bulitin_func[4] = NULL;
	sh_ctx->child_bulitin_func[0] = ft_echo;
	sh_ctx->child_bulitin_func[1] = ft_env;
	sh_ctx->child_bulitin_func[2] = ft_pwd;
	sh_ctx->child_bulitin_func[3] = NULL;
}

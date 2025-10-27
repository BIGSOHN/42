/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:40:00 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/29 19:23:00 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	handle_exception(t_bt_node *node, t_sh_ctx *ctx);

void	exception_handler(const char *str, t_sh_ctx *ctx)
{
	int		*status;
	char	*tmp;

	status = get_exit_status();
	tmp = ft_itoa(errno);
	*status = truncate_8bits(tmp);
	perror(str);
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	exit(*status);
}

static int	handle_exception(t_bt_node *node, t_sh_ctx *ctx)
{
	char		*tmp;
	int			*status;
	struct stat	s_stat;

	(void)node;
	status = get_exit_status();
	if (!ctx->origin_cmd)
	{
		*status = truncate_8bits("0");
		tmp = NULL;
	}
	else
	{
		if (!stat(ctx->origin_cmd, &s_stat))
			if (S_IFDIR == (s_stat.st_mode & S_IFMT))
				errno = 21;
		tmp = get_error_message(ctx, status);
	}
	restore_fd(ctx);
	ft_putstr_fd(tmp, 2);
	ft_lstclear(get_gc(), free);
	exit(*status);
}

void	run_command(t_sh_ctx *ctx, t_bt_node *node, int mode)
{
	char	**exec_path;
	char	*path;
	char	*full_path;

	path = get_path_variable(ctx->env_list->envp_copy);
	if (!path)
		execve(node->cmd[0], node->cmd, ctx->env_list->envp_copy);
	else
	{
		exec_path = ft_split(path, ':');
		while (*exec_path)
		{
			path = ft_strjoin(*exec_path, "/");
			full_path = ft_strjoin(path, node->cmd[0]);
			if (access(full_path, mode) == 0)
			{
				if ((execve(full_path, node->cmd, \
				ctx->env_list->envp_copy)) == -1)
					handle_exception(node, ctx);
			}
			exec_path++;
		}
	}
}

static void	classify_and_run_execve(t_sh_ctx *sh_ctx, t_bt_node *cur_node, \
			int mode, struct stat s_stat)
{
	if ((!ft_strncmp(cur_node->cmd[0], "/", 1))
		|| (!ft_strncmp(cur_node->cmd[0], "./", 2))
		|| (!ft_strncmp(cur_node->cmd[0], "../", 3)))
	{
		if (execve(cur_node->cmd[0], cur_node->cmd, \
			sh_ctx->env_list->envp_copy) == -1)
			handle_exception(cur_node, sh_ctx);
	}
	else
	{
		if (access(cur_node->cmd[0], mode) == 0)
		{	
			if (!stat(sh_ctx->origin_cmd, &s_stat))
			{
				if ((S_IFDIR == (s_stat.st_mode & S_IFMT))
					|| (S_IFREG == (s_stat.st_mode & S_IFMT)))
					run_command(sh_ctx, cur_node, mode);
				else if (execve(cur_node->cmd[0], cur_node->cmd, \
				sh_ctx->env_list->envp_copy) == -1)
					handle_exception(cur_node, sh_ctx);
			}
		}
		else
			run_command(sh_ctx, cur_node, mode);
	}
}

void	check_and_execute(t_bt_node *cur_node, t_sh_ctx *sh_ctx)
{
	int			mode;
	struct stat	s_stat;

	mode = X_OK;
	if (!cur_node->cmd || !cur_node->cmd[0])
		handle_exception(cur_node, sh_ctx);
	if (!execute_builtin_parent(cur_node, sh_ctx))
		postprocess_builtin(sh_ctx);
	if (!execute_builtin_chlid(cur_node, sh_ctx))
		postprocess_builtin(sh_ctx);
	classify_and_run_execve(sh_ctx, cur_node, mode, s_stat);
	handle_exception(cur_node, sh_ctx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:51:25 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/31 17:54:16 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin_chlid(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	size_t	idx;
	size_t	len;

	idx = 0;
	len = ft_strlen(*node->cmd) + 1;
	while (*node->cmd && sh_ctx->child_bulitin_funcs[idx])
	{
		if (!ft_strncmp(*node->cmd, sh_ctx->child_bulitin_funcs[idx], len))
		{
			sh_ctx->child_bulitin_func[idx](node, sh_ctx);
			return (0);
		}
		idx++;
	}
	return (-1);
}

int	execute_builtin_parent(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	size_t	idx;
	size_t	len;
	int		out;

	idx = 0;
	len = ft_strlen(*node->cmd) + 1;
	while (*node->cmd && sh_ctx->parent_bulitin_funcs[idx])
	{
		if (!ft_strncmp(*node->cmd, sh_ctx->parent_bulitin_funcs[idx], len))
		{
			if (node->redir)
				file_redirection(node, sh_ctx);
			if (sh_ctx->is_stdout)
				file_stdout_redirection(&out, sh_ctx);
			sh_ctx->parent_bulitin_func[idx](node, sh_ctx);
			return (0);
		}
		idx++;
	}
	return (-1);
}

int	initialize_exec(t_sh_ctx *ctx)
{
	ctx->buf = ft_calloc(1, sizeof(t_cmd));
	if (ctx->buf == NULL)
		return (0);
	ctx->max_cmd = 10;
	ctx->buf->cmd = ft_calloc(ctx->max_cmd, sizeof(char *));
	if (ctx->buf->cmd == NULL)
		return (0);
	ctx->in_fd = -1;
	ctx->out_fd = -1;
	ctx->pid_table.pids = ft_calloc(\
		ctx->pipe_groups[ctx->cur_group]->cmd_count, sizeof(pid_t));
	if (!ctx->pid_table.pids)
		return (0);
	ctx->pid_table.idx = 0;
	return (1);
}

static void	handle_signal_output(int signal_num, bool is_piped)
{
	int	*flag;

	flag = get_sig_quit_flag();
	if (signal_num == SIGINT)
		ft_putstr_fd("^C\n", 2);
	else if (signal_num == SIGQUIT && *flag == 0)
	{
		if (!is_piped)
			ft_putstr_fd("^\\Quit (core dumped)\n", 2);
		else
			ft_putstr_fd("^\\", 2);
		*flag = 1;
	}
}

int	postprocess(t_sh_ctx *ctx)
{
	int		*status;
	int		idx;
	bool	is_piped_process;

	status = get_exit_status();
	ctx->is_fork = false;
	idx = 0;
	is_piped_process = (ctx->pipe_groups[ctx->cur_group]->cmd_count > 1);
	while (idx < ctx->pipe_groups[ctx->cur_group]->cmd_count)
	{
		waitpid(ctx->pid_table.pids[idx], status, 0);
		if (WIFSIGNALED(*status))
		{
			handle_signal_output(WTERMSIG(*status), is_piped_process);
			if (ctx->pid_table.pids[idx] == \
			ctx->pid_table.pids[ctx->pipe_groups[ctx->cur_group] \
			->cmd_count - 1])
				*status = WTERMSIG(*status) + 128;
		}
		else if (WIFEXITED(*status) && ctx->pid_table.pids[idx] == \
		ctx->pid_table.pids[ctx->pipe_groups[ctx->cur_group]->cmd_count - 1])
			*status = WEXITSTATUS(*status);
		idx++;
	}
	return (0);
}

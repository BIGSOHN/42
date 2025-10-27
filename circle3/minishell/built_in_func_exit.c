/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_exit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:46:25 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/31 19:22:47 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_bt_node *node, t_sh_ctx *ctx)
{
	int	is_numeric_arg;

	is_numeric_arg = 0;
	if (node->word_count >= 2)
		is_numeric_arg = is_numeric_exit_code(node->cmd[1]);
	if (node->word_count > 2)
		handle_multiple_exit_args(node, is_numeric_arg, ctx);
	else if (node->word_count == 2)
		handle_two_exit_args(node, is_numeric_arg, ctx);
	else
		handle_bare_exit(ctx);
}

int	is_numeric_exit_code(char *code)
{
	long long	num;
	char		*llchar;

	llchar = NULL;
	if (ft_check_valid_number(code) == 0 || ft_zero_strlen(code) > 20)
		return (0);
	num = ft_atoll(code);
	if ((num == LLONG_MAX && ft_strlen(code) == 19)
		|| (num == LLONG_MIN && ft_strlen(code) == 20))
		return (1);
	llchar = ft_lltoa(num);
	if (ft_strlen(code) != ft_strlen(llchar))
		return (0);
	return (1);
}

void	handle_multiple_exit_args(t_bt_node *node, int is_num, t_sh_ctx *ctx)
{
	int	*status;

	status = get_exit_status();
	if (is_num == 1)
	{
		if (ctx->pipe_groups[ctx->cur_group]->pipe_count == 0)
			ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		*status = truncate_8bits("1");
	}
	else
	{
		if (ctx->pipe_groups[ctx->cur_group]->pipe_count == 0)
			ft_putstr_fd("exit\n", 2);
		*status = truncate_8bits("2");
		ft_putstr_fd("minishell: exit: ", 2);
		write(2, node->cmd[1], ft_strlen(node->cmd[1]));
		ft_putstr_fd(": numeric argument required\n", 2);
		restore_fd(ctx);
		ft_lstclear(get_gc(), free);
		exit(*status);
	}
}

void	handle_two_exit_args(t_bt_node *node, int is_numeric_arg, t_sh_ctx *ctx)
{
	int	*status;
	int	status_num;

	status = get_exit_status();
	status_num = 0;
	if (is_numeric_arg == 1)
	{
		status_num = ft_atoi(node->cmd[1]);
		*status = status_num;
		if (ctx->pipe_groups[ctx->cur_group]->pipe_count == 0)
			ft_putstr_fd("exit\n", 2);
	}
	else
	{
		if (ctx->pipe_groups[ctx->cur_group]->pipe_count == 0)
			ft_putstr_fd("exit\n", 2);
		*status = truncate_8bits("2");
		ft_putstr_fd("minishell: exit: ", 2);
		write(2, node->cmd[1], ft_strlen(node->cmd[1]));
		ft_putstr_fd(": numeric argument required\n", 2);
	}
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	exit(*status);
}

void	handle_bare_exit(t_sh_ctx *ctx)
{
	int	*status;

	status = get_exit_status();
	*status = 0;
	if (ctx->pipe_groups[ctx->cur_group]->pipe_count == 0)
		ft_putstr_fd("exit\n", 2);
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	exit(*status);
}

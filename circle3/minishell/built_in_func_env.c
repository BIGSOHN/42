/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:01:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:00:19 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_multiple_args(t_bt_node *node, int *status);
static void	handle_single_arg(t_sh_ctx *sh_ctx, int *status);
void		ft_env(t_bt_node *node, t_sh_ctx *sh_ctx);

void	ft_env(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	int	*status;

	status = get_exit_status();
	if (node->word_count == 1)
		handle_single_arg(sh_ctx, status);
	else
		handle_multiple_args(node, status);
}

static void	handle_single_arg(t_sh_ctx *sh_ctx, int *status)
{
	t_env_node	*env_node;
	t_env_node	*under_bar_env_node;

	env_node = sh_ctx->env_list->head;
	under_bar_env_node = NULL;
	while (env_node != NULL)
	{
		if (!ft_strncmp(env_node->envp_key, "_", 2))
			under_bar_env_node = env_node;
		else if (env_node->flag == 1 && env_node->envp_value != NULL)
			printf("%s=%s\n", env_node->envp_key, env_node->envp_value);
		env_node = env_node->next;
	}
	if (under_bar_env_node->flag == 1)
		printf("%s=%s\n",
			under_bar_env_node->envp_key, under_bar_env_node->envp_value);
	*status = truncate_8bits("0");
}

static void	handle_multiple_args(t_bt_node *node, int *status)
{
	ft_putstr_fd("env: '", 2);
	ft_putstr_fd(node->cmd[1], 2);
	ft_putendl_fd("': No such file or directory", 2);
	*status = truncate_8bits("127");
}

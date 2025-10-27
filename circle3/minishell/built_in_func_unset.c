/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_unset.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/15 14:33:50 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	t_env_node	*env_node;
	int			i;
	int			*status;

	i = 1;
	env_node = NULL;
	status = get_exit_status();
	while (i < node->word_count)
	{
		env_node = find_envp_node(sh_ctx->env_list, node->cmd[i]);
		if (env_node != NULL)
		{
			env_node->flag = 0;
			env_node->envp_value = NULL;
		}
		env_node = NULL;
		i++;
	}
	sh_ctx->env_list->envp_copy = envp_join(sh_ctx->env_list);
	*status = truncate_8bits("0");
}

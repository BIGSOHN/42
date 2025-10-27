/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envplist_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:00:07 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/15 14:25:07 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*init_envplist(void)
{
	t_env_list	*envp_list;

	envp_list = ft_malloc(sizeof(t_env_list));
	if (envp_list == NULL)
		exit(1);
	ft_memset(envp_list, 0, sizeof(t_env_list));
	return (envp_list);
}

void	init_envp_shlvl(t_env_list *env_list)
{
	t_env_node	*ptmp;
	int			shlvl;

	ptmp = find_envp_node(env_list, "SHLVL");
	if (ptmp == NULL || ptmp->flag != 1)
		return ;
	if (ft_check_valid_number(ptmp->envp_value) == 0)
		shlvl = 1;
	else
	{
		shlvl = ft_atoi(ptmp->envp_value);
		if (shlvl < 0)
			shlvl = 0;
		else
			shlvl += 1;
	}
	ptmp->envp_value = ft_itoa(shlvl);
}

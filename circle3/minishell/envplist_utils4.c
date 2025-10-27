/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envplist_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:14:28 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/24 20:23:38 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_node	*find_envp_node(t_env_list *envp_list, char *key)
{
	int			i;
	t_env_node	*ptmp;

	i = 0;
	ptmp = envp_list->head;
	while (i < envp_list->size)
	{
		if (ft_strncmp(ptmp->envp_key, key, ft_strlen(key) + 1) == 0)
		{
			if (ft_strlen(ptmp->envp_key) == ft_strlen(key))
				return (ptmp);
		}
		ptmp = ptmp->next;
		i++;
	}
	return (NULL);
}

char	*find_envp_value(t_env_list *envp_list, char *e_key)
{
	int			i;
	t_env_node	*ptmp;

	i = 0;
	ptmp = envp_list->head;
	while (i < envp_list->size)
	{
		if (ft_strncmp(ptmp->envp_key, e_key, ft_strlen(e_key) + 1) == 0)
		{
			if (ft_strlen(ptmp->envp_key) == ft_strlen(e_key))
				return (ptmp->envp_value);
		}
		ptmp = ptmp->next;
		i++;
	}
	return (0);
}

void	print_envplist(t_env_list *envp_list)
{
	t_env_node	*ptmp;
	int			i;

	i = 0;
	ptmp = envp_list->head;
	while (i < envp_list->size)
	{
		printf("key :%s\tvalue :%s\n", ptmp->envp_key, ptmp->envp_value);
		ptmp = ptmp->next;
		i++;
	}
	i = 0;
	while (i < envp_list->size)
	{	
		printf("%s\n", envp_list->envp_copy[i]);
		i++;
	}
}

void	release_envplist(t_env_list *envp_list)
{
	t_env_node	*ptmp;
	t_env_node	*pdelete;
	int			i;

	i = 0;
	ptmp = envp_list->head;
	while (i < envp_list->size)
	{
		free(envp_list->envp_copy[i]);
		i++;
	}
	free(envp_list->envp_copy);
	while (ptmp != NULL)
	{
		pdelete = ptmp;
		ptmp = ptmp->next;
		free(pdelete->envp_key);
		free(pdelete->envp_value);
		free(pdelete);
	}
	free(envp_list);
}

void	release_envpcopy(t_env_list *envp_list)
{
	int	i;

	i = 0;
	while (i < envp_list->size)
	{
		free(envp_list->envp_copy[i]);
		i++;
	}
	free(envp_list->envp_copy);
}

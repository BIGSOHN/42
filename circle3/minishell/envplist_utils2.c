/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envplist_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:31:01 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/15 14:25:25 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*make_envp_list(char **envp)
{
	t_env_list	*envp_list;

	envp_list = init_envplist();
	make_envp_node(envp_list, envp);
	init_envp_shlvl(envp_list);
	envp_list->envp_copy = envp_join(envp_list);
	return (envp_list);
}

void	make_envp_node(t_env_list *envp_list, char **envp)
{
	int		i;
	int		len;
	char	*e_key;
	char	*e_value;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') == NULL)
		{
			len = ft_strlen(envp[i]);
			e_key = ft_substr(envp[i], 0, len);
			e_value = NULL;
		}
		else
		{
			len = ft_strchr(envp[i], '=') - envp[i];
			e_key = ft_substr(envp[i], 0, len);
			e_value = ft_substr(envp[i], len + 1, ft_strlen(envp[i]) - len);
		}
		push_envp_node(envp_list, e_key, e_value);
		i++;
	}
}

void	push_envp_node(t_env_list *envp_list, char *e_key, char *e_value)
{
	if (envp_list->size == 0)
		env_insert_at_first(envp_list, e_key, e_value);
	else
		env_insert_at_back(envp_list, e_key, e_value);
}

void	env_insert_at_first(t_env_list *envp_list, char *e_key, char *e_val)
{
	t_env_node	*p_new_node;

	p_new_node = ft_malloc(sizeof(t_env_node));
	if (p_new_node == NULL)
		exit(1);
	ft_memset(p_new_node, 0, sizeof(t_env_node));
	p_new_node->envp_key = e_key;
	p_new_node->envp_value = e_val;
	p_new_node->flag = 1;
	envp_list->head = p_new_node;
	envp_list->tail = p_new_node;
	envp_list->size++;
}

void	env_insert_at_back(t_env_list *envp_list, char *ekey, char *e_val)
{
	t_env_node	*p_new_node;

	p_new_node = ft_malloc(sizeof(t_env_node));
	if (p_new_node == NULL)
		exit(1);
	ft_memset(p_new_node, 0, sizeof(t_env_node));
	p_new_node->envp_key = ekey;
	p_new_node->envp_value = e_val;
	p_new_node->flag = 1;
	p_new_node->prev = envp_list->tail;
	envp_list->tail->next = p_new_node;
	envp_list->tail = p_new_node;
	envp_list->size++;
}

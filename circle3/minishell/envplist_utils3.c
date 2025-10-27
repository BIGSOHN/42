/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envplist_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:05:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/15 14:26:13 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exrtact_env_key(char *str)
{
	char	*result;
	int		loc;

	result = NULL;
	if (ft_strchr(str, '=') == NULL)
		result = ft_substr(str, 0, ft_strlen(str));
	else
	{
		loc = (ft_strchr(str, '=') - &str[0]);
		if (loc != 0 && str[loc - 1] == '+')
			result = ft_substr(str, 0, loc - 1);
		else if (loc != 0 && str[loc - 1] != '+')
			result = ft_substr(str, 0, loc);
		else if (loc == 0)
			result = NULL;
	}
	return (result);
}

char	*extract_env_value(char *str)
{
	char	*result;
	int		loc;

	result = NULL;
	if (ft_strchr(str, '=') == 0)
		return (result);
	loc = ft_strlen(ft_strchr(str, '=') + 1);
	if (loc == 0)
		result = (char *)ft_calloc(1, sizeof(char));
	else
		result = ft_substr(str, ft_strlen(str) - loc, loc);
	return (result);
}

char	*extract_env_sign(char *str)
{
	int		loc;
	char	*result;

	loc = 0;
	result = NULL;
	if (ft_strchr(str, '=') != 0)
	{
		loc = (ft_strchr(str, '=') - &str[0]);
		if (loc != 0 && str[loc - 1] == '+')
			result = ft_substr(str, loc - 1, 2);
		else if (loc != 0 && str[loc - 1] != '+')
			result = ft_substr(str, loc, 1);
	}
	return (result);
}

char	**envp_join(t_env_list *envp_list)
{
	int			i;
	int			active_count;
	t_env_node	*ptmp;
	char		*temp;
	char		**result;

	i = 0;
	ptmp = envp_list->head;
	active_count = count_active_env_nodes(envp_list);
	result = (char **)ft_calloc(active_count + 1, sizeof(char *));
	if (result == NULL)
		exit(1);
	while (ptmp)
	{
		if (ptmp->flag == 1)
		{
			temp = ft_strjoin(ptmp->envp_key, "=");
			result[i] = ft_strjoin(temp, ptmp->envp_value);
			i++;
		}
		ptmp = ptmp->next;
	}
	return (result);
}

int	count_active_env_nodes(t_env_list *envp_list)
{
	int			count;
	t_env_node	*ptmp;

	count = 0;
	ptmp = envp_list->head;
	while (ptmp != NULL)
	{
		if (ptmp->flag == 1)
			count++;
		ptmp = ptmp->next;
	}
	return (count);
}

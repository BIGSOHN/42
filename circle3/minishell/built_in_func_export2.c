/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_export2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:08:10 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:47:59 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env_vars(t_bt_node *node, t_sh_ctx *sh_ctx, int *status)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (i < node->word_count)
	{
		flag = parse_export_env_command(node->cmd[i], sh_ctx->env_list);
		if (flag == 0)
			*status = truncate_8bits("1");
		i++;
	}
	if (*status != 1)
		*status = truncate_8bits("0");
}

int	parse_export_env_command(char *cmd, t_env_list *env_list)
{
	char	*key;
	char	*value;
	char	*sign;

	key = exrtact_env_key(cmd);
	value = NULL;
	sign = NULL;
	if (is_valid_env_name(key) == 1)
	{
		value = extract_env_value(cmd);
		sign = extract_env_sign(cmd);
		if (ft_strlen(sign) == 2 && ft_strncmp(sign, "+=", 3) == 0)
			extend_env_var(key, value, env_list);
		else
			update_env_var(key, value, env_list);
		return (1);
	}
	else
	{
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		return (0);
	}
}

void	update_env_var(char *key, char *value, t_env_list *env_list)
{
	t_env_node	*env_node;

	env_node = find_envp_node(env_list, key);
	if (env_node != NULL)
	{
		if (env_node->envp_value != NULL && value == NULL)
			env_node->flag = 1;
		else
		{
			env_node->envp_value = value;
			env_node->flag = 1;
		}
	}
	else
		push_envp_node(env_list, key, value);
	env_list->envp_copy = envp_join(env_list);
}

void	extend_env_var(char *key, char *value, t_env_list *env_list)
{
	t_env_node	*env_node;
	char		*join_str;

	env_node = find_envp_node(env_list, key);
	if (env_node != NULL)
	{
		join_str = ft_strjoin(env_node->envp_value, value);
		env_node->envp_value = join_str;
		env_node->flag = 1;
	}
	else
		push_envp_node(env_list, key, value);
	env_list->envp_copy = envp_join(env_list);
}

int	is_valid_env_name(char *key)
{
	int	i;

	i = 1;
	if (key == NULL)
		return (0);
	if (!(ft_isalpha(key[0]) == 1 || key[0] == '_'))
		return (0);
	while (key[i] != '\0')
	{
		if (!(ft_isalnum(key[i]) == 1 || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

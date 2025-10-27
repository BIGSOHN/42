/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:37 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:49:13 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	int	*status;

	status = get_exit_status();
	if (node->word_count == 1)
		move_home(sh_ctx->env_list, status);
	else if (node->word_count > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		*status = 1;
	}
	else
		move_dir(node->cmd[1], sh_ctx->env_list, status);
}

void	move_home(t_env_list *env_list, int *status)
{
	char	*dir;

	dir = find_envp_value(env_list, "HOME");
	if (dir == NULL || chdir(dir) == -1)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		*status = truncate_8bits("1");
	}
	else
		update_pwd_envp(env_list, status);
}

void	move_dir(char *dir, t_env_list *env_list, int *status)
{
	if (ft_strlen(dir) == 1 && dir[0] == '-')
		move_oldpwd(env_list, status);
	else if (ft_strncmp(dir, "--", 3) == 0)
		move_home(env_list, status);
	else
	{
		if (chdir(dir) == -1)
		{
			ft_putstr_fd("bash: cd: ", 2);
			ft_putstr_fd(dir, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			*status = 1;
		}
		else
			update_pwd_envp(env_list, status);
	}
}

void	update_pwd_envp(t_env_list *env_list, int *status)
{
	t_env_node	*oldpwd_node;
	t_env_node	*pwd_node;
	char		*pwd_path;

	oldpwd_node = NULL;
	pwd_node = NULL;
	pwd_path = getcwd(NULL, 0);
	if (pwd_path == NULL)
		exit(1);
	oldpwd_node = find_envp_node(env_list, "OLDPWD");
	if (oldpwd_node->flag == 0)
		oldpwd_node->flag = 1;
	pwd_node = find_envp_node(env_list, "PWD");
	if (pwd_node->flag == 0)
		pwd_node->flag = 1;
	oldpwd_node->envp_value = ft_strdup(pwd_node->envp_value);
	pwd_node->envp_value = ft_strdup(pwd_path);
	free(pwd_path);
	env_list->envp_copy = envp_join(env_list);
	*status = truncate_8bits("0");
}

void	move_oldpwd(t_env_list *env_list, int *status)
{
	t_env_node	*env_node;

	env_node = find_envp_node(env_list, "OLDPWD");
	if (env_node->flag == 0 || env_node->envp_value == NULL)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		*status = truncate_8bits("1");
	}
	else if (chdir(env_node->envp_value) == -1)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		*status = truncate_8bits("1");
	}
	else
		update_pwd_envp(env_list, status);
}

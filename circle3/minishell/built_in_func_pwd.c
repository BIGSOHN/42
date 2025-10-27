/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:57:09 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:02:08 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	char	*pwd;
	int		*status;

	(void)node;
	(void)sh_ctx;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		exit(1);
	printf("%s\n", pwd);
	free(pwd);
	status = get_exit_status();
	*status = truncate_8bits("0");
}

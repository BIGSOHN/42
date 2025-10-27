/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:40:00 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:08:13 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

void	handle_chdir_error(const char *path, char **s, t_sh_ctx *ctx)
{
	(void)s;
	handle_error_type(path);
	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	exit(*get_exit_status());
}

int	change_dir(char *cmd, char *path, char **s, t_sh_ctx *ctx)
{
	if (cmd == NULL)
		return (0);
	if (path == NULL)
		return (0);
	if (!ft_strncmp(path, "./", 3))
		return (0);
	if (chdir(path) == 0)
	{
		*s = cmd;
		return (1);
	}
	else
		handle_chdir_error(path, s, ctx);
	return (0);
}

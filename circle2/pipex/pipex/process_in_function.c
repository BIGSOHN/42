/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_in_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:37:20 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 13:44:59 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_direct_cmd(char **cmd, char **envp)
{
	if (execve(cmd[0], cmd, envp) == -1)
	{
		double_ptr_free(cmd);
		fail_execve_msg_exit();
	}
}

void	child_process_work(char **cmd, char **envp)
{
	char	*working_path;

	working_path = find_working_path(envp, cmd[0]);
	if (execve(working_path, cmd, envp) == -1)
	{
		double_ptr_free(cmd);
		if (working_path != NULL)
			free(working_path);
		fail_execve_msg_exit();
	}
}

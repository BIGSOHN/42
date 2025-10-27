/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:06:44 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/17 16:16:33 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fail_open_msg_exit(void)
{
	perror("No such file or directory\n");
	exit(1);
}

void	fail_pipe_msg_exit(void)
{
	ft_printf("pipe error\n");
	exit(1);
}

void	fail_dup2_msg_exit(void)
{
	perror("dup2 fail\n");
	exit(1);
}

void	fail_execve_msg_exit(void)
{
	perror("Error : command is wrong\n");
	exit(1);
}

void	fail_process_fork(pid_t pid)
{
	if (pid < 0)
	{
		perror("process fork failed\n");
		exit(1);
	}
}

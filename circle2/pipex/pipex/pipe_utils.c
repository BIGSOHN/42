/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:51:17 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/17 16:17:40 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_pipe_and_process_run(char **argv, char **envp)
{
	pid_t	first_child;
	pid_t	second_child;
	int		fd[2];

	if (pipe(fd) == -1)
		fail_pipe_msg_exit();
	first_child = fork();
	if (first_child < 0)
		fail_process_fork(first_child);
	else if (first_child == 0)
		first_child_process(fd, argv, envp);
	else
	{
		second_child = fork();
		if (second_child < 0)
			fail_process_fork(first_child);
		else if (second_child == 0)
			second_child_process(fd, argv, envp);
		else
			parent_process(fd, first_child, second_child);
	}
}

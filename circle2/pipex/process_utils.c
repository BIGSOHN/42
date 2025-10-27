/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 20:11:52 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 20:11:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_process(int *fd, char **argv, char **envp)
{
	char	**cmd;
	char	*working_path;
	int		open_file_fd;

	close(fd[0]);
	open_file_fd = open(argv[1], O_RDONLY);
	if (open_file_fd < 0)
		fail_open_msg_exit();
	if (dup2(open_file_fd, 0) == -1)
		fail_dup2_msg_exit();
	if (dup2(fd[1], 1) == -1)
		fail_dup2_msg_exit();
	close(fd[1]);
	cmd = single_quote_split(argv[2], ' ');
	if (access(cmd[0], X_OK) == 0)
		child_direct_cmd(cmd, envp);
	else
		child_process_work(cmd, envp);
}

void	second_child_process(int *fd, char **argv, char **envp)
{
	char	**cmd;
	int		out_file_fd;

	close(fd[1]);
	out_file_fd = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (out_file_fd < 0)
		fail_open_msg_exit();
	if (dup2(out_file_fd, 1) == -1)
		fail_dup2_msg_exit();
	if (dup2(fd[0], 0) == -1)
		fail_dup2_msg_exit();
	close(fd[0]);
	cmd = single_quote_split(argv[3], ' ');
	if (access(cmd[0], X_OK) == 0)
		child_direct_cmd(cmd, envp);
	else
		child_process_work(cmd, envp);
}

void	parent_process(int *fd, pid_t first_child, pid_t second_child)
{
	int	status;

	close(fd[0]);
	close(fd[1]);
	waitpid(first_child, &status, 0);
	waitpid(second_child, &status, 0);
}

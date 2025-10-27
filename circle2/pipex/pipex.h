/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:13:09 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 19:15:59 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft/libft.h"

int		main(int argc, char **argv, char **envp);
char	**split_envp(char **envp);
char	*path_join(char *path, char *cmd);
char	*find_working_path(char **envp, char *cmd);
void	make_pipe_and_process_run(char **argv, char **envp);
void	first_child_process(int *fd, char **argv, char **envp);
void	second_child_process(int *fd, char **argv, char **envp);
void	parent_process(int *fd, pid_t first_child, pid_t second_child);
void	child_direct_cmd(char **cmd, char **envp);
void	child_process_work(char **cmd, char **envp);
void	double_ptr_free(char **dest);
char	**single_quote_split(char *s, char c);
int		single_quote_word_count(char *s, char c);
char	**single_quote_word_split(char **dest, char *src, char sep);
void	meet_and_move_idx(char *src, char sep, int *i);
int		count_word_length(char *src, char sep, int *i);
int		count_in_quote(char *src, char sep, int *i);
size_t	single_quote_strlcpy(char *dst, const char *src, size_t size);
void	fail_open_msg_exit(void);
void	fail_pipe_msg_exit(void);
void	fail_dup2_msg_exit(void);
void	fail_execve_msg_exit(void);
void	fail_process_fork(pid_t pid);
#endif
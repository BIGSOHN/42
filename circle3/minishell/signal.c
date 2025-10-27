/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:09:31 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/02 13:50:52 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_sigterm(void)
{
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_lstclear(get_gc(), free);
	exit (0);
}

void	sigint_handler(int signal_number, siginfo_t *info, void *context)
{
	int	*status;

	(void)signal_number;
	(void)info;
	(void)context;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("^C\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	status = get_exit_status();
	*status = 130;
}

void	init_signal_attr(t_sh_ctx *ctx)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	(void)ctx;
	sigemptyset(&sig_int.sa_mask);
	sig_int.sa_flags = SA_SIGINFO;
	sig_int.sa_sigaction = &sigint_handler;
	sigemptyset(&sig_quit.sa_mask);
	sig_quit.sa_flags = 0;
	sig_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig_int, NULL);
	sigaction(SIGQUIT, &sig_quit, NULL);
}

void	null_handle_exception(t_redir *redir, int fd, t_sh_ctx *ctx)
{
	int	*status;

	status = get_exit_status();
	ft_putstr_fd("\nminishell: warning: ", 2);
	ft_putstr_fd("here-document at line 17 delimited", 2);
	ft_putstr_fd(" by end-of-file (wanted ", 2);
	ft_putstr_fd(ft_strjoin(redir->limiter, "')\n"), 2);
	close(fd);
	(void)ctx;
	check_here_doc(ctx->origin_dir, ctx, UNLINK);
	*status = truncate_8bits("0");
}

void	sigint_handle_exception(t_redir *redir, int fd, t_sh_ctx *ctx)
{
	int	*status;

	(void)redir;
	status = get_exit_status();
	close(fd);
	check_here_doc(ctx->origin_dir, ctx, UNLINK);
	(void)ctx;
	*status = truncate_8bits("130");
}

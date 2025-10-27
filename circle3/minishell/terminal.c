/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:17:21 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/26 13:00:54 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_terminal_print_off(void)
{
	struct termios	term;

	tcgetattr(STDOUT_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}

void	set_parent_term_attr(void)
{
	struct sigaction	sa_parent_int;
	struct sigaction	sa_parent_quit;

	sa_parent_int.sa_handler = SIG_IGN;
	sigemptyset(&sa_parent_int.sa_mask);
	sa_parent_int.sa_flags = 0;
	sigaction(SIGINT, &sa_parent_int, NULL);
	sa_parent_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_parent_quit.sa_mask);
	sa_parent_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_parent_quit, NULL);
}

void	set_here_doc_terminal_attr(t_sh_ctx *ctx)
{
	struct sigaction	sa_here_doc_int;
	struct sigaction	sa_here_doc_quit;

	(void)ctx;
	sa_here_doc_int.sa_handler = do_sigint_heredoc;
	sigemptyset(&sa_here_doc_int.sa_mask);
	sa_here_doc_int.sa_flags = 0;
	sigaction(SIGINT, &sa_here_doc_int, NULL);
	sa_here_doc_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_here_doc_quit.sa_mask);
	sa_here_doc_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_here_doc_quit, NULL);
}

void	init_term_attr(void)
{
	struct termios		term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

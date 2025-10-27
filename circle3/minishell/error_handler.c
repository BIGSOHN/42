/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:30:37 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/24 20:24:40 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_sigint_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("^C\n", STDERR_FILENO);
	g_flag = SIGINT;
}

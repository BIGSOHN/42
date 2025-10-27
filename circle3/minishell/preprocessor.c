/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:13:04 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:49:23 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	preprocess(char *line, t_sh_ctx **sh_ctx, char **envp)
{
	int	*flag;

	(void)envp;
	flag = get_sig_quit_flag();
	*flag = 0;
	if (!line)
		process_sigterm();
	if (ft_strncmp(line, "", 1) == 0)
		return (0);
	if (check_syntax(line) == 0)
		return (0);
	add_history(line);
	init_shell_cmd(*sh_ctx);
	init_shell_funcs(*sh_ctx);
	return (1);
}

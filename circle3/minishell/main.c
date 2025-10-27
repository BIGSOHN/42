/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:33:02 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:46:48 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_flag = 0;

int	set_home_path(t_sh_ctx *ctx, char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "HOME=", 5))
		{
			ctx->home_path = ft_strdup(*envp + 5);
			return (0);
		}
		envp++;
	}
	return (-1);
}

void	init_shell_context(t_sh_ctx **sh_ctx, char **envp)
{
	*sh_ctx = ft_calloc(1, sizeof(t_sh_ctx));
	if (!(*sh_ctx))
		exit(1);
	(*sh_ctx)->syntax_error = ft_malloc(sizeof(struct s_syntax_error));
	if (!(*sh_ctx)->syntax_error)
		exit(1);
	(*sh_ctx)->env_list = make_envp_list(envp);
	set_home_path(*sh_ctx, envp);
}

void	backup_fd(t_sh_ctx *ctx)
{
	ctx->backup_fd.stdin = dup(STDIN_FILENO);
	if (ctx->backup_fd.stdin == -1)
	{
		perror("stdin dup2 error");
		exit(1);
	}
	ctx->backup_fd.stdout = dup(STDOUT_FILENO);
	if (ctx->backup_fd.stdout == -1)
	{
		perror("stdout dup2 error");
		exit(1);
	}
}

int	process_cmd(char *line, t_sh_ctx *ctx)
{
	bool	flag;

	if (tokenize(line, ctx))
		return (0);
	if (parse_command(ctx))
		return (0);
	backup_fd(ctx);
	flag = exec_command(ctx);
	restore_fd(ctx);
	if (flag)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_sh_ctx		*sh_ctx;
	char			*line;
	char			*trimed_line;

	(void)argc;
	(void)argv;
	init_shell_context(&sh_ctx, envp);
	init_term_attr();
	while (1)
	{
		g_flag = 0;
		init_signal_attr(sh_ctx);
		line = readline("minishell> ");
		trimed_line = ft_strtrim(line, "\t ");
		free(line);
		if (!preprocess(trimed_line, &sh_ctx, envp))
			continue ;
		process_cmd(trimed_line, sh_ctx);
	}
}

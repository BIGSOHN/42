/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 21:40:00 by woonhan           #+#    #+#             */
/*   Updated: 2025/01/01 15:49:38 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_relative_path(char **s, t_sh_ctx *ctx)
{
	char	*path;
	char	*cmd;
	size_t	end;
	int		len;

	cmd = NULL;
	path = NULL;
	len = ft_strlen(*s);
	end = len;
	while (len - 1 > 0)
	{
		if ((*s)[len - 1] == '/')
		{
			path = ft_substr(*s, 0, len);
			cmd = ft_substr(*s, len, end);
			break ;
		}
		len--;
	}
	if (change_dir(cmd, path, s, ctx))
		return (1);
	return (0);
}

char	*get_error_message(t_sh_ctx *ctx, int *status)
{
	ft_putstr_fd("minishell: ", 2);
	if (errno == ENOENT)
	{
		*status = truncate_8bits("127");
		if (!ft_strchr(ctx->origin_cmd, '/'))
			return (ft_strjoin(ctx->origin_cmd, ": command not found\n"));
		return (ft_strjoin(ctx->origin_cmd, ": No such file or directory\n"));
	}
	if (errno == EACCES || errno == EISDIR || errno == ENOTDIR)
		*status = truncate_8bits("126");
	if (errno == EACCES)
		return (ft_strjoin(ctx->origin_cmd, ": permission denied\n"));
	if (errno == EISDIR)
	{
		if (!ft_strchr(ctx->origin_cmd, '/'))
			return (ft_strjoin(ctx->origin_cmd, ": command not found\n"));
		return (ft_strjoin(ctx->origin_cmd, ": Is a directory\n"));
	}
	if (errno == ENOTDIR)
		return (ft_strjoin(ctx->origin_cmd, ": Not a directory\n"));
	*status = truncate_8bits("1");
	return (ft_strdup("Error: execve failed\n"));
}

void	postprocess_builtin(t_sh_ctx *ctx)
{
	int	*status;

	restore_fd(ctx);
	ft_lstclear(get_gc(), free);
	status = get_exit_status();
	exit(*status);
}

void	print_error_and_set_status(const char *message, const char *path, \
		const char *status_code)
{
	int	*status;

	status = get_exit_status();
	ft_putstr_fd(ft_strjoin(ft_strjoin(message, path), "\n"), 2);
	*status = truncate_8bits((char *)status_code);
}

void	handle_error_type(const char *path)
{
	if (errno == EACCES)
		print_error_and_set_status("Error: Permission denied for path '", \
		path, "126");
	else if (errno == ENOENT)
		print_error_and_set_status("Error: Directory '", path, "127");
	else if (errno == ENOTDIR || errno == ENAMETOOLONG)
		print_error_and_set_status("Error: Invalid path '", path, "126");
	else
	{
		perror("Error: ");
		*get_exit_status() = truncate_8bits("1");
	}
}

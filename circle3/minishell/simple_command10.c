/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command10.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:27:17 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:46:06 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_home_path(const char *path)
{
	if (!path || !*path)
		return (0);
	return (path[0] == '~' && (path[1] == '\0' || path[1] == '/'));
}

char	*get_path_after_home(const char *path)
{
	if (!path || !*path || path[0] != '~')
		return (NULL);
	if (path[1] == '\0')
		return (ft_strdup(""));
	if (path[1] == '/')
		return (ft_strdup(path + 2));
	return (NULL);
}

int	special_path(t_token *tok, t_sh_ctx *ctx)
{
	char	*remaining_path;
	int		result;

	(void)ctx;
	if (!tok || !tok->str)
		return (-1);
	if (!is_home_path(tok->str))
		return (-1);
	if (ft_strlen(tok->str) == 1)
		return (0);
	remaining_path = get_path_after_home(tok->str);
	if (!remaining_path)
		return (-1);
	if (*remaining_path)
	{
		result = validate_path(remaining_path);
		if (!result)
			return (-1);
	}
	return (0);
}

int	simple_command(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	return (process_command_tokens(tok, ctx, &temp));
}

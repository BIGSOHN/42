/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:36:37 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:49:44 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*get_sig_quit_flag(void)
{
	static int	flag;

	return (&flag);
}

int	*get_exit_status(void)
{
	static int	status;

	return (&status);
}

char	*ft_realloc(char *chunk, int *size)
{
	char	*new;

	new = ft_calloc(*size * 2, sizeof(char));
	if (new == NULL)
		exit (0);
	ft_memcpy(new, chunk, sizeof(char) * *size);
	*size *= 2;
	return (new);
}

char	*get_path_variable(char **envp)
{
	char	*path;

	path = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			path = ft_strdup(*envp + 5);
			break ;
		}
		envp++;
	}
	return (path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:44:58 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 19:23:51 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**split_envp(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
		{	
			path = ft_split(ft_strchr(envp[i], '/'), ':');
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*path_join(char *path, char *cmd)
{
	char	*full_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*find_working_path(char **envp, char *cmd)
{
	int		i;
	char	**path_list;
	char	*full_path;

	i = -1;
	path_list = split_envp(envp);
	while (path_list[++i] != 0)
	{
		full_path = path_join(path_list[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			double_ptr_free(path_list);
			return (full_path);
		}
		free(full_path);
	}
	double_ptr_free(path_list);
	return (NULL);
}

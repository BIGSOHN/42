/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:37:52 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:22:41 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory_component(const char *str)
{
	if (str[0] == '.' && str[1] == '.' && (!str[2] || str[2] == '/'))
		return (1);
	if (str[0] == '.' && (!str[1] || str[1] == '/'))
		return (1);
	return (0);
}

int	validate_path_component(const char *component, size_t len)
{
	size_t	i;

	if (len == 0)
		return (0);
	if (component[0] == '\0' || component[0] == '/'
		|| component[0] == '<' || component[0] == '>'
		|| component[0] == '|' || component[0] == ';'
		|| component[0] == '&' || component[0] == '*'
		|| component[0] == '\t' || component[0] == '\n')
		return (0);
	i = 0;
	while (i < len)
	{
		if (component[i] == '\0' || component[i] == '<'
			|| component[i] == '>' || component[i] == '|'
			|| component[i] == ';' || component[i] == '&'
			|| component[i] == '*' || component[i] == '\t'
			|| component[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

const char	*find_next_component(const char *current)
{
	const char	*next_slash;

	if (ft_strncmp(current, "./", 2) == 0)
		return (current + 2);
	next_slash = ft_strchr(current, '/');
	if (!next_slash)
		next_slash = current + ft_strlen(current);
	return (next_slash);
}

int	process_path_component(const char **current)
{
	const char	*next_slash;
	size_t		component_len;

	next_slash = find_next_component(*current);
	component_len = next_slash - *current;
	if (is_directory_component(*current))
	{
		*current = next_slash;
		if (**current == '/')
			(*current)++;
		return (1);
	}	
	if (!validate_path_component(*current, component_len))
		return (0);
	*current = next_slash;
	if (**current == '/')
		(*current)++;
	return (1);
}

int	validate_path(const char *path)
{
	const char	*current;
	int			is_absolute;

	current = path;
	is_absolute = (*path == '/');
	if (is_absolute)
		current++;
	while (*current)
	{
		if (!process_path_component(&current))
			return (0);
	}
	return (1);
}

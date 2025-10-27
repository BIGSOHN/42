/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:08:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/12 14:41:05 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*s;
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (0);
	result = buffer_check(&s, &buffer, fd);
	if (buffer == NULL)
	{
		if (result == NULL)
			free(s);
		s = 0;
	}
	free(buffer);
	return (result);
}

char	*buffer_check(char **s_val, char **buffer, int fd)
{
	char	*temp;
	char	*res;
	int		r_count;
	int		i;

	res = *s_val;
	while (ft_strchr(res, '\n') == NULL)
	{
		r_count = read(fd, *buffer, BUFFER_SIZE);
		if (r_count == -1 || r_count == 0)
			return (error_end_file(r_count, res, buffer));
		(*buffer)[r_count] = '\0';
		temp = res;
		res = ft_strjoin(temp, *buffer);
		free(temp);
	}
	i = ft_strlen(ft_strchr(res, '\n') + 1);
	temp = res;
	*s_val = ft_substr(temp, ft_strlen(temp) - i, i);
	res = ft_substr(temp, 0, ft_strlen(temp) - i);
	free(temp);
	return (res);
}

char	*error_end_file(int r_count, char *res, char **buffer)
{
	char	*temp;

	temp = *buffer;
	*buffer = NULL;
	free(temp);
	if (ft_strlen(res) == 0 || r_count == -1)
	{
		return (0);
	}
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:08:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:40:35 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*s;
	char		*result;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = (char *)ft_malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (0);
	ft_memset(buffer, 0, BUFFER_SIZE + 1);
	result = buffer_check(&s, &buffer, fd);
	if (buffer == NULL)
	{
		s = 0;
	}
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
	}
	i = ft_strlen(ft_strchr(res, '\n') + 1);
	temp = res;
	*s_val = ft_substr(temp, ft_strlen(temp) - i, i);
	res = ft_substr(temp, 0, ft_strlen(temp) - i);
	return (res);
}

char	*error_end_file(int r_count, char *res, char **buffer)
{
	*buffer = NULL;
	if (ft_strlen(res) == 0 || r_count == -1)
	{
		return (0);
	}
	return (res);
}

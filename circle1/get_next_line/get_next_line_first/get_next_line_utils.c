/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:09:00 by ssohn             #+#    #+#             */
/*   Updated: 2024/04/25 16:19:26 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	const int	total_length = ft_strlen(s1) + ft_strlen(s2);
	int			i;
	int			j;
	char		*temp;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * (total_length + 1));
	if (total_length == 0 || temp == 0 || (s1 == NULL && s2 == NULL))
		return (0);
	while (s1 != NULL && s1[i] != '\0')
	{
		temp[i] = s1[i];
		++i;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		temp[i + j] = s2[j];
		++j;
	}
	temp[i + j] = '\0';
	return (temp);
}

int	ft_strlen(char *s)
{
	int	length;

	length = 0;
	if (s == NULL)
		return (0);
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*dest;
	int		s_len;
	int		i;
	int		start_len;

	i = 0;
	s_len = ft_strlen(s);
	start_len = ft_strlen(&s[start]);
	if (s_len <= start)
		len = 0;
	if (start_len < len)
		len = start_len;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (0);
	while (i < len && s[start + i] != '\0')
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	else
		return (0);
}

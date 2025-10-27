/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:57:46 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/09 12:12:27 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	s_len;
	size_t	i;
	size_t	start_len;

	i = 0;
	s_len = ft_strlen(s);
	start_len = ft_strlen(&s[start]);
	if (s_len <= start)
		len = 0;
	if (start_len < len)
		len = start_len;
	dest = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	while (i < len && s[start + i] != '\0')
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

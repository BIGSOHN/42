/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:32:16 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/21 19:51:01 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		length;
	char	*dest;

	length = 0;
	if (s == NULL)
		return (NULL);
	while (s[length] != '\0')
		length++;
	dest = (char *)ft_malloc(sizeof(char) * (length + 1));
	if (dest == 0)
		return (0);
	length = 0;
	while (s[length] != '\0')
	{
		dest[length] = s[length];
		length++;
	}
	dest[length] = '\0';
	return (dest);
}

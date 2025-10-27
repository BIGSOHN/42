/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:32:16 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/12 16:21:34 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		length;
	char	*dest;

	length = 0;
	while (s[length] != '\0')
		length++;
	dest = (char *)malloc(sizeof(char) * (length + 1));
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

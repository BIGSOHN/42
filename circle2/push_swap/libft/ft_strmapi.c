/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:43:09 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/13 13:13:38 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				length;
	char			*result;

	i = 0;
	length = ft_strlen(s);
	if (s == 0)
		return (0);
	result = (char *)malloc(sizeof(char) * (length + 1));
	if (result == 0)
		return (0);
	while (s[i] != '\0')
	{
		result[i] = (f)(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

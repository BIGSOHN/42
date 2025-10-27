/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:43:09 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/09 12:12:15 by woonhan          ###   ########.fr       */
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
	result = (char *)ft_malloc(sizeof(char) * (length + 1));
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

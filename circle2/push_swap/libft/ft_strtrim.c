/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:47:31 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/14 09:55:32 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		length;
	char	*start;
	char	*end;
	char	*temp;

	i = 0;
	if (s1 == 0)
		return (0);
	length = ft_strlen(s1);
	while (ft_strchr(set, (int)s1[i]) != 0 && s1[i] != '\0')
		i++;
	start = (char *)&s1[i];
	while (length > i && ft_strchr(set, (int)s1[length]) != 0)
		length--;
	end = (char *)&s1[length];
	if (*s1 == 0)
		length = 0;
	if (start <= end)
		length = end - start + 1;
	temp = (char *)malloc(sizeof(char) * (length + 1));
	if (temp == 0)
		return (0);
	ft_strlcpy(temp, &s1[i], length + 1);
	return (temp);
}

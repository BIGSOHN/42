/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:19:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/13 13:42:44 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_length;
	size_t	i;
	char	*temp;

	total_length = 0;
	i = 0;
	total_length += ft_strlen(s1);
	total_length += ft_strlen(s2);
	temp = (char *)malloc(sizeof(char) * (total_length + 1));
	if (temp == 0)
		return (0);
	while (*s1 != '\0')
	{
		temp[i] = *s1;
		i++;
		s1++;
	}
	while (*s2 != '\0')
	{
		temp[i] = *s2;
		i++;
		s2++;
	}
	temp[i] = '\0';
	return (temp);
}

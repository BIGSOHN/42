/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:19:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/03 16:21:43 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
		i++;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		temp[i + j] = s2[j];
		j++;
	}
	temp[i + j] = '\0';
	return (temp);
}

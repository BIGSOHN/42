/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:48:13 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/12 21:38:05 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (t1[i] != '\0' || t2[i] != '\0'))
	{
		if (t1[i] > t2[i])
			return (1);
		else if (t1[i] < t2[i])
			return (-1);
		else
			i++;
	}
	return (0);
}

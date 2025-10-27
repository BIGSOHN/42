/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:56:54 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/18 11:15:59 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*result;
	size_t			i;
	size_t			temp;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	temp = nmemb * size;
	if (temp / nmemb != size)
		return (0);
	result = (unsigned char *)malloc(temp);
	if (!result)
		return (0);
	while (i < size * nmemb)
	{
		result[i] = 0;
		i++;
	}
	return ((void *)result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:25:04 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/13 14:01:28 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_length;
	size_t	s_length;
	size_t	i;

	s_length = ft_strlen(src);
	if (size == 0)
		return (s_length);
	d_length = ft_strlen(dst);
	i = 0;
	if (d_length > size)
		return (size + s_length);
	while (src[i] != '\0' && i + 1 + d_length < size)
	{
		dst[d_length + i] = src[i];
		i++;
	}
	dst[d_length + i] = '\0';
	return (d_length + s_length);
}

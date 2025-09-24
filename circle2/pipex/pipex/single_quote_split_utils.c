/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_split_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:25:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 19:46:30 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	meet_and_move_idx(char *src, char sep, int *i)
{
	if (src[*i] == '\'')
		(*i)++;
	while (src[*i] != '\'' && src[(*i) + 1] != '\0')
		(*i)++;
	if (src[*i] == '\'' && (src[(*i) + 1] != '\0' && src[(*i) + 1] != sep))
		(*i)++;
}

int	count_word_length(char *src, char sep, int *i)
{
	int	len;

	len = 0;
	while ((src[*i] != '\0') && (src[*i] != '\'') && (src[*i] != sep))
	{
		len++;
		(*i)++;
	}
	if (src[*i] == '\'')
		len += count_in_quote(src, sep, i);
	return (len);
}	

int	count_in_quote(char *src, char sep, int *i)
{
	int	len;

	len = 0;
	if (src[*i] == '\'')
		(*i)++;
	while (src[*i] != '\'' && src[(*i) + 1] != '\0')
	{
		len++;
		(*i)++;
	}
	if (src[*i] == '\'' && src[(*i) + 1] != '\0')
		(*i)++;
	while (src[*i] != '\0' && src[*i] != sep)
	{
		len++;
		(*i)++;
	}
	return (len);
}

size_t	single_quote_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	j = 0;
	while (src[i] != '\0' && j + 1 < size)
	{
		if (src[i] != '\'')
		{
			dst[j] = src[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:54:42 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:40:02 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c);
static char	**ft_word_split(char **dest, char *src, char sep);
static char	**ft_free(int num);
char		**ft_split(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	int		count;
	char	**result;

	count = ft_word_count(s, c);
	result = (char **)ft_malloc(sizeof(char *) * (count + 1));
	if (result == 0)
		return (0);
	result[count] = 0;
	result = ft_word_split(result, (char *)s, c);
	return (result);
}

static int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (((s[i] == c && len > 0) || (s[i] != c && s[i + 1] == '\0')))
		{
			len = 0;
			count++;
		}
		if (s[i] != c)
			len++;
		i++;
	}
	return (count);
}

static char	**ft_word_split(char **dest, char *src, char sep)
{
	int		len;
	int		i;
	int		j;
	char	*temp;

	len = 0;
	i = -1;
	j = -1;
	while (src[++i] != '\0')
	{
		if (src[i] != sep && len == 0)
			temp = &src[i];
		if (src[i] != sep)
			len++;
		if ((src[i] == sep && len > 0) || (src[i + 1] == '\0' && src[i] != sep))
		{
			dest[++j] = (char *)ft_malloc(sizeof(char) * (len + 1));
			if (dest[j] == 0)
				return ((ft_free(j)));
			ft_strlcpy(dest[j], temp, len + 1);
			len = 0;
		}
	}
	return (dest);
}

static char	**ft_free(int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		i++;
	}
	return (0);
}

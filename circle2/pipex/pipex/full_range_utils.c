/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_range_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:24:11 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 20:13:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	double_ptr_free(char **dest)
{
	int	i;

	i = 0;
	while (dest[i] != NULL)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

char	**single_quote_split(char *s, char c)
{
	int		count;
	char	**result;

	count = single_quote_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (result == 0)
		return (0);
	result[count] = 0;
	result = single_quote_word_split(result, s, c);
	return (result);
}

int	single_quote_word_count(char *s, char c)
{
	int	count;
	int	i;
	int	flag;

	count = 0;
	i = 0;
	flag = 1;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			flag = 1;
		if ((s[i] != c && flag == 1) || (s[i] == '\'' && flag == 1))
		{
			count++;
			flag = 0;
			if (s[i] == '\'')
				meet_and_move_idx(s, c, &i);
		}
		i++;
	}
	return (count);
}

char	**single_quote_word_split(char **dest, char *src, char sep)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	i = 0;
	j = -1;
	while (src[i] != '\0')
	{
		if ((src[i] != sep) || (src[i] == '\''))
		{
			temp = &src[i];
			len = count_word_length(src, sep, &i);
			dest[++j] = (char *)malloc(sizeof(char) * len + 1);
			if (dest[j] == NULL)
			{
				double_ptr_free(dest);
				return (NULL);
			}
			single_quote_strlcpy(dest[j], temp, len + 1);
		}
		else
			i++;
	}
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:52:24 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/24 20:19:03 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quoteline_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	char	*str;
	int		i;
	int		quoteline_len;

	quoteline_len = 0;
	i = 0;
	while (rdline[quoteline_len + 1] != first_delim)
		quoteline_len++;
	if (quoteline_len != 0)
	{
		str = (char *)ft_calloc(quoteline_len + 1 + 2, sizeof(char));
		if (str == NULL)
			exit(1);
		str[i] = first_delim;
		i++;
		while (rdline[i] != first_delim)
		{
			str[i] = rdline[i];
			i++;
		}
		str[i] = first_delim;
		fill_literal_token(tok_list, str, LITERAL);
	}
	return (quoteline_len);
}

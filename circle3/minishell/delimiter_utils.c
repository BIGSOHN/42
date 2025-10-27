/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:20:07 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:02:44 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	envp_key_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = 0;
	(void)first_delim;
	if (find_prev_token_type(tok_list->tail) == HERE_DOCUMENT)
		return (next_heredoc_token(tok_list, rdline));
	if (rdline[len + 1] == '?')
		len = 1;
	else
		while (check_delim_envp_symbol(rdline[len + 1]) == 0)
			len++;
	str = (char *)ft_calloc(len + 2, sizeof(char));
	if (str == NULL)
		exit(1);
	while (rdline[i] != '\0' && i < len + 1)
	{
		str[i] = rdline[i];
		i++;
	}
	push_token(tok_list, str, LITERAL);
	return (len + 1);
}

int	single_quote_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		len;

	len = 2;
	len += quoteline_token(tok_list, first_delim, rdline);
	return (len);
}

int	double_quote_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		len;

	len = 2;
	len += quoteline_token(tok_list, first_delim, rdline);
	return (len);
}

int	single_quoteline_token(t_tok_list *tok_list, char first_delim, char *rdline)
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
		str = (char *)ft_calloc(quoteline_len + 1, sizeof(char));
		if (str == NULL)
			exit(1);
		while (rdline[i + 1] != first_delim)
		{
			str[i] = rdline[i + 1];
			i++;
		}
		fill_literal_token(tok_list, str, LITERAL);
	}
	return (quoteline_len);
}

int	doulbe_quoteline_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		i;
	char	rd_str[2];
	char	*temp;
	char	*result;

	i = 0;
	result = NULL;
	while (rdline[++i] != first_delim)
	{
		ft_bzero(rd_str, sizeof(rd_str));
		rd_str[0] = rdline[i];
		if (rd_str[0] == '$')
		{
			fill_literal_token(tok_list, result, LITERAL);
			i += envp_key_token(tok_list, rd_str[0], &rdline[i]) - 1;
			result = NULL;
			continue ;
		}
		temp = result;
		result = ft_strjoin(temp, rd_str);
	}
	fill_literal_token(tok_list, result, LITERAL);
	return (i);
}

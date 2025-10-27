/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:51:10 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:34:12 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	i = 0;
	while (rdline[len] == first_delim && len < 2)
		len++;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		exit(1);
	while (i < len)
	{
		str[i] = first_delim;
		i++;
	}
	push_token(tok_list, str, REDIRECTION);
	return (len);
}

int	logic_pipe_token(t_tok_list *tok_list, char first_delim, char *rdline)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	i = 0;
	while (rdline[len] == first_delim)
		len++;
	if (len > 2)
		len = 2;
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		exit(1);
	while (i < len)
	{
		str[i] = first_delim;
		i++;
	}
	push_token(tok_list, str, LOGIC_PIPE);
	return (len);
}

int	parenthesis_token(t_tok_list *tok_list, char first_delim)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	if (str == NULL)
		exit(1);
	str[0] = first_delim;
	push_token(tok_list, str, PARENTHESIS);
	return (1);
}

int	white_space_token(t_tok_list *tok_list, char first_delim)
{
	char	*str;

	str = (char *)ft_calloc(2, sizeof(char));
	if (str == NULL)
		exit(1);
	if (first_delim == '\t')
		first_delim = ' ';
	str[0] = first_delim;
	if (tok_list-> tail != NULL)
		if (tok_list->tail->token_type != WHITE_SPACE)
			push_token(tok_list, str, WHITE_SPACE);
	return (1);
}

int	next_heredoc_token(t_tok_list *tok_list, char *rdline)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	i = 0;
	while (rdline[len] != '\0')
	{
		if (ft_strchr("<>\"\'|&() ", rdline[len]) == 0)
			len++;
		else
			break ;
	}
	str = (char *)ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		exit(1);
	while (i < len)
	{
		str[i] = rdline[i];
		i++;
	}
	fill_literal_token(tok_list, str, LITERAL);
	return (len);
}

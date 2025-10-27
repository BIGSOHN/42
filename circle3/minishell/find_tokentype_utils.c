/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokentype_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:45:13 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/24 20:42:13 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	notice_token_type(char *str, int token_type)
{
	if (token_type == LITERAL || token_type == WORD
		|| token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE
		|| token_type == ENVP_KEY || token_type == WHITE_SPACE)
		return (token_type);
	else if (token_type == REDIRECTION)
		return (redir_token_type(str));
	else if (token_type == LOGIC_PIPE)
		return (lp_token_type(str));
	else if (token_type == PARENTHESIS)
		return (parenthesis_token_type(str));
	return (-1);
}

int	redir_token_type(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2 && str[0] == '<')
		return (HERE_DOCUMENT);
	if (len == 1 && str[0] == '<')
		return (INPUT_REDIRECTION);
	if (len == 2 && str[0] == '>')
		return (APPEND_REDIRECTION);
	if (len == 1 && str[0] == '>')
		return (OUTPUT_REDIRECTION);
	return (-1);
}

int	lp_token_type(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len == 2 && str[0] == '&')
		return (LOGICAL_AND);
	if (len == 1 && str[0] == '&')
		return (BACKGROUND);
	if (len == 2 && str[0] == '|')
		return (LOGICAL_OR);
	if (len == 1 && str[0] == '|')
		return (PIPE);
	return (-1);
}

int	parenthesis_token_type(char *str)
{
	if (str[0] == '(')
		return (OPEN_PARENTHESIS);
	if (str[0] == ')')
		return (CLOSE_PARENTHESIS);
	return (-1);
}

int	find_prev_token_type(t_token *ptoken)
{
	t_token	*ptmp;

	ptmp = ptoken;
	while (ptmp != NULL)
	{
		if (ptmp->token_type != WHITE_SPACE)
			return (ptmp->token_type);
		ptmp = ptmp->prev;
	}
	return (-1);
}

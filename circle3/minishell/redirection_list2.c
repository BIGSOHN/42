/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:27:10 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/26 09:40:01 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_sequence(t_token *tok, t_syntax_error *temp)
{
	if (!tok || !tok->next)
		return (0);
	if (is_redirection(tok->str) && is_redirection(tok->next->str))
	{
		if (!tok->next->next)
		{
			set_temp_error(temp, tok->str, ERR_INVALID_SEQUENCE);
			return (-1);
		}
		if (ft_strlen(tok->str) == 1 && ft_strlen(tok->next->str) == 1)
		{
			set_temp_error(temp, tok->next->str, ERR_CONSECUTIVE_OPERATOR);
			return (-1);
		}
	}
	return (0);
}

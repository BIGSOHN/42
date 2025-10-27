/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tokentype_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:53:03 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/24 20:53:03 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(t_token *ptk)
{
	if (ptk->token_type == INPUT_REDIRECTION
		|| ptk->token_type == OUTPUT_REDIRECTION
		|| ptk->token_type == HERE_DOCUMENT
		|| ptk->token_type == APPEND_REDIRECTION)
		return (1);
	return (0);
}

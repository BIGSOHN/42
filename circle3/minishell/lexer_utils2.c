/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 22:31:36 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 00:02:48 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_temp_error(t_syntax_error *temp)
{	
	temp->token = NULL;
	temp->type = ERR_NONE;
}

void	set_temp_error(t_syntax_error *temp, char *token, t_error_type type)
{
	temp->token = token;
	temp->type = type;
}

void	apply_error(t_sh_ctx *ctx, t_syntax_error *temp)
{
	if (temp->type != ERR_NONE)
	{
		ctx->syntax_error->token = temp->token;
		ctx->syntax_error->type = temp->type;
	}
}

int	command(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok)
		return (-1);
	if (check_initial_command(tok, &temp) == -1)
	{
		apply_error(ctx, &temp);
		return (-1);
	}
	if (process_command_elements(tok, ctx, &temp) == -1)
		return (-1);
	return (redirection_list(tok, ctx));
}

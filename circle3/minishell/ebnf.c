/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ebnf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:09:53 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:03:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_operator_error(char *token_str, t_error_type type)
{
	(void)type;
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token_str)
	{
		if (ft_strncmp(token_str, "||", 2) == 0)
			ft_putstr_fd("||", 2);
		else if (ft_strncmp(token_str, "&&", 2) == 0)
			ft_putstr_fd("&&", 2);
		else if (ft_strncmp(token_str, "&", 1) == 0)
			ft_putstr_fd("&", 2);
		else
			ft_putstr_fd(token_str, 2);
	}
	ft_putendl_fd("'", 2);
}

void	print_syntax_error(t_sh_ctx *ctx)
{
	if (!ctx || !ctx->syntax_error || ctx->syntax_error->type == ERR_NONE)
		return ;
	if (ctx->syntax_error->type == ERR_CONSECUTIVE_OPERATOR
		|| ctx->syntax_error->type == ERR_INVALID_SEQUENCE)
	{
		print_operator_error(ctx->syntax_error->token, \
							ctx->syntax_error->type);
		return ;
	}
	ft_putendl_fd("minishell: syntax error", 2);
}

int	is_redirection(char *str)
{
	if (!str || !*str)
		return (0);
	return (*str == '<' || *str == '>');
}

int	is_pipe(char *str)
{
	if (!str || !*str)
		return (0);
	return (*str == '|');
}

int	is_operator(char *str)
{
	return (is_redirection(str) || is_pipe(str));
}

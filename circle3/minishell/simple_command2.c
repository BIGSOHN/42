/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 14:37:52 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 17:46:19 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_heredoc_operator(t_token *tok)
{
	t_token	*prev;

	prev = tok->prev;
	while (prev && prev->token_type == WHITE_SPACE)
		prev = prev->prev;
	if (prev && prev->token_type == HERE_DOCUMENT)
		return (prev);
	return (NULL);
}

int	filename(t_token *tok, t_sh_ctx *ctx)
{
	t_syntax_error	temp;

	init_temp_error(&temp);
	if (!tok || !tok->str || !*tok->str)
		return (-1);
	if (tok->str[0] == '$')
		return (0);
	if (!validate_path(tok->str))
	{
		set_temp_error(&temp, tok->str, ERR_INVALID_NAME);
		apply_error(ctx, &temp);
		return (-1);
	}
	return (0);
}

int	regularfile(t_token *tok, t_sh_ctx *ctx)
{
	char			*s;
	t_syntax_error	temp;	

	init_temp_error(&temp);
	s = tok->str;
	if (namepart_no_dot(&s, ctx) == 0)
	{
		if (*s == '.')
		{
			s++;
			if (!check_regular_extension(&s, &temp, ctx))
			{
				apply_error(ctx, &temp);
				return (-1);
			}
		}
		return (0);
	}
	set_temp_error(&temp, s, ERR_INVALID_REGULAR_FILE);
	apply_error(ctx, &temp);
	return (-1);
}

int	hiddenfile(t_token *tok, t_sh_ctx *ctx)
{
	char			*s;
	t_syntax_error	temp;

	init_temp_error(&temp);
	s = tok->str;
	if (*s != '.')
		return (-1);
	s++;
	if (process_hidden_name(&s, &temp, ctx) == 0)
		return (0);
	apply_error(ctx, &temp);
	return (-1);
}

int	is_valid_path_char(char c)
{
	if (c == '\0' || c == '<' || c == '>' || c == '|'
		|| c == ';' || c == '&' || c == '(' || c == ')'
		|| c == ' ' || c == '\t' || c == '\n' || c == '*')
		return (0);
	return (1);
}

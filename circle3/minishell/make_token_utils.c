/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:34:07 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:37:04 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *rdline, t_sh_ctx *sh_ctx)
{
	t_tok_list	*token_list;

	token_list = init_tokenlist();
	make_token(token_list, rdline);
	if (lexer(token_list->head, sh_ctx))
		return (-1);
	change_token_type_to_literal(token_list);
	join_continuous_token(token_list);
	while (find_token_node(token_list, WHITE_SPACE) != 0)
		delete_token_node(token_list, WHITE_SPACE);
	sh_ctx->tok_list = init_dbl_tokenlist();
	make_dbl_list(token_list, sh_ctx->tok_list);
	return (0);
}

void	make_token(t_tok_list *token_list, char *rdline)
{
	int		i;
	char	*temp;
	char	*result;
	char	rd_str[2];

	i = -1;
	result = NULL;
	while (rdline[++i] != '\0')
	{
		ft_bzero(rd_str, sizeof(rd_str));
		rd_str[0] = rdline[i];
		if (check_delim(rd_str[0]) == 1)
		{
			if (result != NULL)
				fill_literal_token(token_list, result, WORD);
			i = fill_delim_token(token_list, &rdline[i], rd_str) + i - 1;
			result = NULL;
			continue ;
		}
		temp = result;
		result = ft_strjoin(temp, rd_str);
	}
	if (result != NULL)
		fill_literal_token(token_list, result, WORD);
}

int	check_delim(char rd_char)
{
	if (ft_strchr("<>\"\'|&()$\t ", rd_char) == 0)
		return (0);
	else
		return (1);
}

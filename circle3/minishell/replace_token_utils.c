/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:10:35 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:20:04 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_delim_envp_symbol(char rd_char)
{
	if (ft_strchr("<>\"\'|&()$ ", rd_char) == 0
		&& ft_strchr("!#%%*+-,.:;=?@[]\\^`{}~", rd_char) == 0)
		return (0);
	else
		return (1);
}

void	replace_envp_token(t_tok_list *token_list, t_env_list *envp_list)
{
	t_token	*ptmp;
	int		i;

	i = 0;
	ptmp = token_list->head;
	while (i < token_list->size)
	{
		if (ptmp->token_type == ENVP_KEY)
			change_envp_str(ptmp, envp_list);
		ptmp = ptmp->next;
		i++;
	}
}

void	change_envp_str(t_token *p_token, t_env_list *envp_list)
{
	char	*e_key;
	char	*e_value;

	e_key = p_token->str;
	if (ft_strlen(e_key) == 1)
		e_value = e_key;
	else
		e_value = find_envp_value(envp_list, &e_key[1]);
	change_envp_key_to_value(p_token, e_value);
}

void	change_envp_key_to_value(t_token *p_token, char *e_value)
{
	if (e_value != NULL)
		p_token->str = ft_strdup(e_value);
	else
		p_token->str = NULL;
	p_token->token_type = LITERAL;
}

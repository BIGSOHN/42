/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_tokenlist_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:36:41 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/26 15:01:18 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_dbl_list(t_tok_list *tok_list, t_dbl_list *dbl_list)
{
	int			count;
	int			rd_count;
	int			null_cnt;
	char		**strs;
	t_token		*ptmp;

	ptmp = tok_list->head;
	while (ptmp != NULL)
	{
		count = count_token(ptmp);
		rd_count = count_redir_before_delim(ptmp);
		null_cnt = count_null_before_delim(ptmp);
		strs = make_continuous_token_strs(ptmp, count - rd_count - null_cnt);
		push_dbl_token(dbl_list, strs,
			ptmp->token_type, count - rd_count - null_cnt);
		while (count != 0)
		{
			if (is_redirection_token(ptmp) == 1)
				push_redirection(dbl_list, ptmp->str, ptmp->next->str);
			ptmp = ptmp->next;
			count--;
		}
	}
}

char	**make_continuous_token_strs(t_token *ptk, int wc)
{
	char	**strs;
	int		i;

	i = 0;
	strs = (char **)ft_calloc(wc + 1, sizeof(char *));
	if (strs == NULL)
		exit(1);
	while (i < wc && ptk != NULL)
	{
		if (ptk->prev != NULL && is_redirection_token(ptk->prev) == 1)
		{
			ptk = ptk->next;
			continue ;
		}
		if (ptk->str != NULL && is_redirection_token(ptk) == 0)
		{
			strs[i] = ft_strdup(ptk->str);
			if (strs[i] == NULL)
				exit(1);
			i++;
		}
		ptk = ptk->next;
	}
	return (strs);
}

void	push_redirection(t_dbl_list *dbl_list, char *sign, char *file)
{
	if (dbl_list->tail->redir == NULL)
		insert_redir_fst(dbl_list, sign, file);
	else
		insert_redir_last(dbl_list, sign, file);
}

void	insert_redir_fst(t_dbl_list *dbl_list, char *sign, char *file)
{
	t_redir	*redir;

	redir = ft_malloc(sizeof(t_redir));
	if (redir == NULL)
		exit(1);
	ft_memset(redir, 0, sizeof(t_redir));
	redir->redir_sign = ft_strdup(sign);
	redir->file_name = ft_strdup(file);
	redir->origin_file_name = ft_strdup(file);
	dbl_list->tail->redir = redir;
}

void	insert_redir_last(t_dbl_list *dbl_list, char *sign, char *file)
{
	t_redir	*redir;
	t_redir	*ptmp;

	ptmp = dbl_list->tail->redir;
	redir = ft_malloc(sizeof(t_redir));
	if (redir == NULL)
		exit(1);
	ft_memset(redir, 0, sizeof(t_redir));
	redir->redir_sign = ft_strdup(sign);
	redir->file_name = ft_strdup(file);
	redir->origin_file_name = ft_strdup(file);
	while (ptmp->next != NULL)
		ptmp = ptmp->next;
	ptmp->next = redir;
}

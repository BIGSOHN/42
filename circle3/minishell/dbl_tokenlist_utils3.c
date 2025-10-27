/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_tokenlist_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:16:48 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 15:58:42 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dbllist(t_dbl_list *dbl_list)
{
	t_dbl_token	*ptmp;
	int			i;
	int			j;

	i = 0;
	ptmp = dbl_list->head;
	while (i < dbl_list->size)
	{
		j = 0;
		printf("word count :%d\ttoken type :%d\n",
			ptmp->word_count, ptmp->token_type);
		while (j < ptmp->word_count)
		{
			printf("str[%d]:%s\n", j, ptmp->strs[j]);
			j++;
		}
		if (ptmp->redir != NULL)
			print_redir(ptmp->redir);
		ptmp = ptmp->next;
		i++;
	}
}

void	print_redir(t_redir *ptmp)
{
	while (ptmp != NULL)
	{
		printf("sign:\t%s\n", ptmp->redir_sign);
		printf("file name:\t%s\n", ptmp->file_name);
		ptmp = ptmp->next;
	}
}

void	release_dbllist(t_dbl_list *dbl_list)
{
	t_dbl_token	*ptmp;
	t_dbl_token	*pdelete;
	int			i;
	int			j;

	i = 0;
	ptmp = dbl_list->head;
	while (i < dbl_list->size)
	{
		j = 0;
		pdelete = ptmp;
		ptmp = ptmp->next;
		while (j < pdelete->word_count)
		{
			free(pdelete->strs[j]);
			j++;
		}
		if (pdelete->redir != NULL)
			release_redir(pdelete->redir);
		free(pdelete->strs);
		free(pdelete);
		i++;
	}
	free(dbl_list);
}

void	release_redir(t_redir *ptmp)
{
	t_redir	*pdel;

	while (ptmp != NULL)
	{
		pdel = ptmp;
		ptmp = ptmp->next;
		free(pdel->file_name);
		free(pdel->redir_sign);
		free(pdel);
	}	
}

int	count_token(t_token *ptmp)
{
	int	count;

	if (ptmp->token_type != OPEN_PARENTHESIS
		&& (ptmp->token_type == PIPE
			|| ptmp->token_type == LOGICAL_AND
			|| ptmp->token_type == LOGICAL_OR))
		count = count_continuous_token(ptmp);
	else if (ptmp->token_type == OPEN_PARENTHESIS)
		count = count_covered_parenthesis_token(ptmp);
	else
		count = count_before_delim(ptmp);
	return (count);
}

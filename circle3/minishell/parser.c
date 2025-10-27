/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:42:41 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/24 23:32:38 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bt_node	*create_node(t_dbl_token **tok, t_bt_node **node)
{
	if (!*node)
	{
		*node = ft_malloc(sizeof(t_bt_node));
		if (!*node)
			exit(0);
	}
	if (!tok)
	{
		(*node)->cmd = 0;
		(*node)->type = 0;
		(*node)->word_count = 0;
		(*node)->redir = 0;
	}
	else
	{
		(*node)->cmd = (*tok)->strs;
		(*node)->type = (*tok)->token_type;
		(*node)->word_count = (*tok)->word_count;
		(*node)->redir = (*tok)->redir;
	}
	(*node)->depth = 0;
	(*node)->left = NULL;
	(*node)->right = NULL;
	return (*node);
}

void	parse_subshell(t_ast_info *ast_info)
{
	(void)ast_info->tok;
}

char	**dup_2d_array(char **src)
{
	char	**copy;
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (src[count])
		count++;
	copy = ft_malloc((count + 1) * sizeof(char *));
	if (!copy)
		return (0);
	while (i < count)
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			return (0);
		i++;
	}
	copy[count] = NULL;
	return (copy);
}

t_bt_node	*copy_node(t_bt_node *orignal)
{
	t_bt_node	*copy;

	copy = ft_malloc(sizeof(t_bt_node));
	if (copy == NULL)
		return (0);
	copy->cmd = dup_2d_array(orignal->cmd);
	copy->type = orignal->type;
	copy->word_count = orignal->word_count;
	copy->depth = 0;
	copy->left = NULL;
	copy->right = NULL;
	return (copy);
}

void	reallocate_pipegroups(t_sh_ctx *sh_ctx)
{
	t_pipe_group	**new;

	new = ft_calloc(sh_ctx->max_group * 2, sizeof(t_pipe_group *));
	if (!new)
		exit(0);
	ft_memcpy(new, sh_ctx->pipe_groups, sizeof(sh_ctx->pipe_groups));
	sh_ctx->pipe_groups = new;
	sh_ctx->max_group = sh_ctx->max_group * 2;
}

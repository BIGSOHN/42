/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 17:42:41 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:17:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pipe_group(t_sh_ctx *ctx)
{
	if (++ctx->cur_group > ctx->max_group)
		reallocate_pipegroups(ctx);
	ctx->pipe_groups[ctx->cur_group] = \
	ft_calloc(ctx->max_group, sizeof(t_pipe_group));
	if (ctx->pipe_groups[ctx->cur_group] == NULL)
		exit(0);
}

void	set_root(t_ast_info *ast_info, t_bt_node **orig_cur, t_sh_ctx *sh_ctx)
{	
	t_bt_node	**cpy_node;

	if ((*ast_info->tok)->token_type == LOGICAL_AND
		|| (*ast_info->tok)->token_type == LOGICAL_OR)
		add_pipe_group(sh_ctx);
	if ((*ast_info->tok)->token_type == PIPE)
		sh_ctx->pipe_groups[sh_ctx->cur_group]->pipe_count++;
	cpy_node = ft_malloc(sizeof(t_bt_node *));
	if (!cpy_node)
		exit(0);
	*cpy_node = copy_node(*ast_info->cur);
	(*cpy_node)->left = *ast_info->root;
	*ast_info->root = *cpy_node;
	*ast_info->cur = NULL;
	*orig_cur = *cpy_node;
}

int	set_binary_tree(t_ast_info *ast_info, t_sh_ctx *ctx)
{
	t_dbl_token	*orig_tok;
	t_bt_node	*orig_cur;

	*ast_info->cur = create_node(ast_info->tok, ast_info->cur);
	orig_tok = *ast_info->tok;
	orig_cur = *ast_info->cur;
	if (!*ast_info->root)
		*ast_info->root = *ast_info->cur;
	if ((*ast_info->tok)->token_type != WORD
		&& (*ast_info->tok)->token_type != LITERAL
		&& (*ast_info->tok)->token_type != HERE_DOCUMENT)
		set_root(ast_info, &orig_cur, ctx);
	if ((*ast_info->tok)->token_type == LITERAL)
		ctx->pipe_groups[ctx->cur_group]->cmd_count++;
	if (((*ast_info->tok)->token_type == LITERAL) && (*ast_info->tok)->redir)
		if (check_here_doc((*ast_info->tok)->redir, ctx, WRITE))
			return (-1);
	if (orig_tok != NULL && orig_tok->next != NULL)
	{
		ast_info->tok = &orig_tok->next;
		ast_info->cur = &orig_cur->right;
		set_binary_tree(ast_info, ctx);
	}
	return (0);
}

void	set_pipe_groups(t_sh_ctx *ctx)
{	
	ctx->pipe_groups = ft_calloc(ctx->max_group, sizeof(t_pipe_group *));
	if (ctx->pipe_groups == NULL)
		exit(0);
	ctx->pipe_groups[++ctx->cur_group] = \
	ft_calloc(ctx->max_group, sizeof(t_pipe_group));
	if (ctx->pipe_groups[ctx->cur_group] == NULL)
		exit(0);
	ctx->pipe_groups[ctx->cur_group]->pipes[0] = -1;
	ctx->pipe_groups[ctx->cur_group]->pipes[1] = -1;
}

int	parse_command(t_sh_ctx *ctx)
{
	t_dbl_token		*tok;

	ctx->ast_info = ft_calloc(1, sizeof(t_ast_info));
	if (ctx->ast_info == NULL)
		exit(0);
	tok = ctx->tok_list->head;
	ctx->ast_info->tok = &tok;
	ctx->ast_info->root = ft_calloc(1, sizeof(t_bt_node *));
	if (ctx->ast_info->root == NULL)
		return (0);
	ctx->ast_info->cur = ft_calloc(1, sizeof(t_bt_node *));
	if (ctx->ast_info->cur == NULL)
		return (0);
	ctx->max_group = 10;
	ctx->cur_group = -1;
	set_pipe_groups(ctx);
	if (set_binary_tree(ctx->ast_info, ctx))
		return (-1);
	return (0);
}

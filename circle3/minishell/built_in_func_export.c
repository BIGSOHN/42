/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:10:41 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 14:01:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_arr(t_env_node *pcount, t_env_list *env_list);

void	ft_export(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	int		*status;

	status = get_exit_status();
	if (node->word_count == 1)
		export_print(sh_ctx, status);
	else
		export_env_vars(node, sh_ctx, status);
}

void	export_print(t_sh_ctx *sh_ctx, int *status)
{
	t_env_node	*env_node;
	int			*arr;
	int			i;
	int			count;

	count = 0;
	arr = make_sorting_arr(sh_ctx->env_list);
	while (count < sh_ctx->env_list->size)
	{
		env_node = sh_ctx->env_list->head;
		i = -1;
		while (env_node->next != NULL && arr[++i] != count)
			env_node = env_node->next;
		if (env_node->flag == 1)
		{
			printf("declare -x %s", env_node->envp_key);
			if (env_node->envp_value != NULL)
				printf("=\"%s\"", env_node->envp_value);
			printf("\n");
		}
		count++;
	}
	*status = truncate_8bits("0");
}

int	*make_sorting_arr(t_env_list *env_list)
{
	int			*arr;
	int			i;
	t_env_node	*ptmp;

	ptmp = env_list->head;
	arr = (int *)ft_calloc(env_list->size, sizeof(int));
	if (arr == NULL)
		exit(1);
	i = 0;
	while (ptmp != NULL)
	{
		arr[i] = count_arr(ptmp, env_list);
		i++;
		ptmp = ptmp->next;
	}
	return (arr);
}

static int	count_arr(t_env_node *pcount, t_env_list *env_list)
{
	int			count;
	t_env_node	*ptmp;

	count = 0;
	ptmp = env_list->head;
	while (ptmp != NULL)
	{
		if ((ft_strncmp(ptmp->envp_key, pcount->envp_key,
					ft_strlen(ptmp->envp_key) + 1) == -1))
			count++;
		ptmp = ptmp->next;
	}
	return (count);
}

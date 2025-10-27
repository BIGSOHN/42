/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_func_echo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:33:35 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:51:29 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_not_option(char **strs, int wc);
static void	print_strs(char **strs, int wc, int place);

void	ft_echo(t_bt_node *node, t_sh_ctx *sh_ctx)
{
	char	**cmd;
	int		place;
	int		*status;

	(void)sh_ctx;
	cmd = node->cmd;
	if (ft_strlen(cmd[0]) == 4
		&& ft_strncmp(cmd[0], "echo", ft_strlen("echo") + 1) == 0)
	{
		place = find_not_option(cmd, node->word_count);
		print_strs(cmd, node->word_count, place);
		if (place == 1)
			ft_putstr_fd("\n", 1);
	}
	status = get_exit_status();
	*status = truncate_8bits("0");
}

static int	find_not_option(char **strs, int wc)
{
	int	i;
	int	j;

	i = 0;
	while (++i < wc)
	{
		j = 0;
		if (strs[i][0] == '-')
		{
			while (strs[i][++j] != '\0')
			{
				if (strs[i][j] != 'n')
					return (i);
			}
		}
		else
			return (i);
	}
	return (i);
}

static void	print_strs(char **strs, int wc, int place)
{
	while (place < wc)
	{
		ft_putstr_fd(strs[place], 1);
		if (place != wc - 1)
			ft_putstr_fd(" ", 1);
		place++;
	}
}

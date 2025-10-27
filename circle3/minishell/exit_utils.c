/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:17:11 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/25 14:39:35 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_command(char **s, char *chunk, t_sh_ctx *ctx, int *i)
{
	char	*tmp;
	int		*status;
	int		idx;

	status = get_exit_status();
	if ((!ft_strncmp(*s, "$?", 2)))
	{
		*s += 2;
		tmp = ft_itoa(*status);
		idx = ft_strlen(tmp);
		ft_strlcpy(chunk, tmp, idx + 1);
		*i = idx;
		return (0);
	}
	if (!ft_strncmp(*s, "~", 1))
	{
		idx = ft_strlen(ctx->home_path);
		ft_strlcpy(chunk, ctx->home_path, idx + 1);
		*i = idx;
		(*s)++;
		return (0);
	}
	return (-1);
}

int	my_exit(long long code)
{
	long long	exit_code;

	exit_code = code % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}

int	contains_digit(char	*s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
	{
		if (!isdigit(s[idx]))
			return (-1);
		idx++;
	}
	return (0);
}

long long	truncate_8bits(char *str)
{
	size_t		idx;
	int			is_negative;
	long long	result;

	idx = 0;
	result = 0;
	is_negative = 1;
	if (!str)
		return (0);
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '-' || str[idx == '+'])
	{
		if (str[idx] == '-')
			is_negative *= -1;
	}
	while (str[idx] >= 48 && str[idx] <= 57)
	{
		result = result * 10 + (str[idx] - '0');
		idx++;
	}
	result *= is_negative;
	return (my_exit(result));
}

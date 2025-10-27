/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:29:49 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 13:57:20 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *rdline)
{
	char	*nqline;
	int		*status;

	status = get_exit_status();
	if (check_quote(rdline) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		*status = truncate_8bits("2");
		return (0);
	}
	nqline = (char *)ft_calloc(len_except_qline(rdline) + 1, sizeof(char));
	if (nqline == NULL)
		exit(1);
	nqline = make_except_quoteline(rdline, nqline);
	if (check_parenthesis(nqline) == 0)
	{
		ft_putstr_fd("syntax error\n", 2);
		*status = truncate_8bits("2");
		return (0);
	}
	return (1);
}

int	check_quote(char *rdline)
{
	int		open_flag;
	int		i;
	char	first_meet_quote;

	i = -1;
	open_flag = 0;
	first_meet_quote = '\0';
	while (rdline[++i] != '\0')
	{
		if ((rdline[i] == '\'' || rdline[i] == '\"') && open_flag == 0)
		{
			open_flag = 1;
			first_meet_quote = rdline[i];
		}
		else if (first_meet_quote == rdline[i] && open_flag == 1)
		{
			open_flag = 0;
			first_meet_quote = '\0';
		}
	}
	if (open_flag == 1)
		return (0);
	return (1);
}

int	check_parenthesis(char *rdline)
{
	int		open_count;
	int		open_flag;
	int		i;

	i = -1;
	open_count = 0;
	open_flag = 0;
	while (rdline[++i] != '\0')
	{
		if (rdline[i] == '(')
		{
			open_count++;
			if (open_flag == 0)
				open_flag = 1;
		}
		else if (rdline[i] == ')')
		{
			open_count--;
			if (open_flag == 1 && open_count == 0)
				open_flag = 0;
		}
	}
	if (open_count == 0 && open_flag == 0)
		return (1);
	return (0);
}

char	*make_except_quoteline(char *rdline, char *nqline)
{
	int		i;
	int		j;
	int		open_flag;
	char	first_meet_quote;

	i = -1;
	j = -1;
	open_flag = 0;
	first_meet_quote = '\0';
	while (rdline[++i] != '\0')
	{
		if ((rdline[i] == '\'' || rdline[i] == '\"') && open_flag == 0)
		{
			open_flag = 1;
			first_meet_quote = rdline[i];
		}
		else if (first_meet_quote == rdline[i] && open_flag == 1)
			open_flag = 0;
		else if (open_flag == 0 && rdline[i] != '\'' && rdline[i] != '\"')
			nqline[++j] = rdline[i];
	}
	return (nqline);
}

int	len_except_qline(char *rdline)
{
	int		quote_len;
	int		i;
	int		open_flag;
	char	first_meet_quote;

	i = -1;
	quote_len = 0;
	open_flag = 0;
	while (rdline[++i] != '\0')
	{
		if ((rdline[i] == '\'' || rdline[i] == '\"') && open_flag == 0)
		{
			open_flag = 1;
			first_meet_quote = rdline[i];
			quote_len++;
		}
		else if (open_flag == 1)
		{
			if (first_meet_quote == rdline[i])
				open_flag = 0;
			quote_len++;
		}
	}
	return (ft_strlen(rdline) - quote_len);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:04:29 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/19 10:14:41 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*res;

	res = *lst;
	if (*lst == 0 && new != 0)
	{
		*lst = new;
		return ;
	}
	else if (lst == 0 || new == 0)
		return ;
	while (res -> next != NULL)
		res = res -> next;
	res->next = new;
}

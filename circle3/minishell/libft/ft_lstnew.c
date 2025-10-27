/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:54:59 by ssohn             #+#    #+#             */
/*   Updated: 2024/12/25 19:26:27 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*p_lst;

	p_lst = (t_list *)malloc(sizeof(t_list) * 1);
	if (p_lst == NULL)
		return (NULL);
	p_lst->content = content;
	p_lst->next = NULL;
	return (p_lst);
}

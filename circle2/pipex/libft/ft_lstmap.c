/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:32 by ssohn             #+#    #+#             */
/*   Updated: 2024/03/19 10:14:26 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;
	t_list	*add_temp;

	add_temp = 0;
	result = lst;
	while (result != 0)
	{
		temp = ft_lstnew((f)(result->content));
		if (temp == 0)
		{
			ft_lstclear(&add_temp, del);
			return (0);
		}
		ft_lstadd_back(&add_temp, temp);
		result = result -> next;
	}
	temp = 0;
	return (add_temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:24:32 by ssohn             #+#    #+#             */
/*   Updated: 2024/11/13 16:07:16 by ssohn            ###   ########.fr       */
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
		if (temp == NULL)
			return (0);
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

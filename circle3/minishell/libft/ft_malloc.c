/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:59:21 by woonhan           #+#    #+#             */
/*   Updated: 2024/12/24 20:10:00 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	**get_gc(void)
{
	static t_list	*gc_list;

	return (&gc_list);
}

void	*ft_malloc(size_t ms)
{
	t_list	**gc;
	void	*new;

	gc = get_gc();
	new = malloc(ms);
	if (!new)
		return (0);
	else
		ft_lstadd_back(gc, ft_lstnew(new));
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   .main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:40:12 by ssohn             #+#    #+#             */
/*   Updated: 2024/05/07 17:00:21 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
int main()
{
	int count1 = 0;
	int count2 = 0;

	count1 = ft_printf("%s", "Hello World");
	ft_printf("\n1:%d 2:%d",count1, count2);

	count2 = printf("%s", "Hello World");
	printf("\n1:%d 2:%d", count1, count2);
	return 0;
}

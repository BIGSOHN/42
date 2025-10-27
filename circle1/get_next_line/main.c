/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:47:05 by ssohn             #+#    #+#             */
/*   Updated: 2024/05/16 16:24:09 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"
# include <stdio.h>

int main()
{
	int fd = 0;
		//open("test", O_RDONLY);
	printf("buffer = %d\n", BUFFER_SIZE);
	printf("fd = %d\n", fd);

	char *line = get_next_line(fd);
	int i = 1;
	// printf("%d line : %s)\n",i,line);
	while (line)
	{
		printf("### %d line : %s$$$\n",i,line);
		free (line);
		line = get_next_line(fd);
		i++;
	}
	printf("### %d line : %s$ ###\n",i,line);

	free (line);
	close(fd);

	return (0);
}

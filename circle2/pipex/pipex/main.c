/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:12:14 by ssohn             #+#    #+#             */
/*   Updated: 2024/07/18 20:08:57 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	**path_list;

	if (argc != 5)
	{
		ft_printf("argument must be four\n");
		exit(1);
	}
	make_pipe_and_process_run(argv, envp);
	return (0);
}

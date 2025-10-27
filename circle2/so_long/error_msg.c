/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:07:14 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/12 11:15:02 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	fail_proper_argument_msg_exit(void)
{
	ft_printf("Error\n");
	ft_printf("Argument must be two\n");
	exit(1);
}

void	fail_open_msg_exit(int fd)
{
	close(fd);
	ft_printf("Error\n");
	perror("Please make a proper map file\n");
	exit(1);
}

void	fail_map_valid_msg_exit_free(void)
{
	ft_printf("Error\n");
	ft_printf("The map is not valid\n");
	exit(1);
}

void	fail_valid_file_exetension_msg_exit(void)
{
	ft_printf("Error\n");
	ft_printf("The file exetension must \".ber\"\n");
	exit(1);
}

void	fail_file_is_empty_msg_exit(void)
{
	ft_printf("Error\n");
	ft_printf("The file is empty\n");
	exit(1);
}

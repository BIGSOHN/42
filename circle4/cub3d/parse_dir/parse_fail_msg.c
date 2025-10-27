/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fail_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:45:00 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/26 17:19:28 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	fail_proper_argument_msg_exit(void)
{
	printf("Error\nArgument must be two\n");
	exit(1);
}

void	fail_valid_file_exetension_msg_exit(void)
{
	printf("Error\nThe file exetension must \".cub\"\n");
	exit(1);
}

void	fail_open_msg_exit(void)
{
	printf("Error\nFailed to open file\n");
	exit(1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:09:48 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/26 17:19:51 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

int	check_valid_file_exetension(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 5) == 0)
		return (1);
	return (0);
}

int	open_scene_file(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		fail_proper_argument_msg_exit();
	if (check_valid_file_exetension(argv) == 0)
		fail_valid_file_exetension_msg_exit();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fail_open_msg_exit();
	return (fd);
}

int	check_file_info(t_file_info	*info)
{
	if (info->error_flag == 1)
	{
		printf("Error\nInvalid texture configuration\n");
		return (1);
	}
	if (info->count_settings != 6)
	{
		printf("Error\nInvalid texture configuration\n");
		return (1);
	}
	if (info->full_flag != 2)
	{
		printf("Error\nMap string does not exist\n");
		return (1);
	}
	if (validate_floor_ceiling_rgb(info) == 1)
		return (1);
	if (check_map_content(info->map_content) == 1)
		return (1);
	return (0);
}

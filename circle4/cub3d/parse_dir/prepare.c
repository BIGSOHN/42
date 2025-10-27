/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:22:34 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:32:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

t_map_data	*prepare_cub3d(int argc, char **argv)
{
	t_file_info	*info;
	t_map_data	*data;

	info = parse_scene_config(argc, argv);
	data = NULL;
	if (check_file_info(info) == 1)
	{
		free_file_info(info);
		return (NULL);
	}
	data = convert_info_to_data(info);
	free_file_info(info);
	if (check_surrounding_cells(data) == 1)
	{
		printf("Error: Map is not surrounded by walls\n");
		free_map_data(data);
		return (NULL);
	}
	return (data);
}

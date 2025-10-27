/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:49:36 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:31:59 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

int	parse_info(t_file_info *info, char *line)
{
	if (info->full_flag != 1)
		parse_texture(info, line);
	else if (info->full_flag == 1 && info->count_settings == 6)
		parse_map(info, line);
	return (0);
}

t_file_info	*parse_scene_config(int argc, char **argv)
{
	t_file_info	*info;
	char		*line;
	int			fd;

	fd = open_scene_file(argc, argv);
	info = ft_calloc(1, sizeof(t_file_info));
	if (info == NULL)
		exit(1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_info(info, line);
		free(line);
		line = get_next_line(fd);
	}
	if (info->map_content != NULL && info->full_flag == 1)
		info->full_flag = 2;
	close(fd);
	return (info);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:34:45 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/09 10:57:43 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_path	*init_path(t_path *path)
{
	path = malloc(sizeof(t_path));
	if (path == NULL)
		exit (0);
	ft_memset(path, 0, sizeof(t_path));
	return (path);
}

void	set_path_param(t_path *path, char **input_map)
{
	path->map = input_map;
	path->collect = count_collectible_element(path->map);
	set_path_position(path, input_map);
}

void	set_path_position(t_path *path, char **input_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < count_map_line(input_map))
	{
		x = 0;
		while (input_map[y][x] != '\0')
		{
			if (input_map[y][x] == 'P')
			{
				path->pos_x = x;
				path->pos_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	release_path_struct(t_path*path)
{
	double_ptr_free(path->map);
	free(path);
}

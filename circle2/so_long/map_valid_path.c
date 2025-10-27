/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:54:15 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/09 10:56:15 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_path(char **map)
{
	t_path	*path;

	path = init_path(path);
	set_path_param(path, map);
	dfs(path, path->pos_y, path->pos_x);
	if (path->valid_path == 1 && path->collect == 0)
	{
		release_path_struct(path);
		return (1);
	}
	release_path_struct(path);
	return (0);
}

void	dfs(t_path *path, int y, int x)
{
	if (path->map[y][x] == '1' || path->map[y][x] == 'V')
		return ;
	if (path->map[y][x] == 'C')
		path->collect--;
	if (path->map[y][x] == 'E')
	{
		path->valid_path = 1;
		return ;
	}
	path->map[y][x] = 'V';
	dfs(path, y + 1, x);
	dfs(path, y - 1, x);
	dfs(path, y, x + 1);
	dfs(path, y, x - 1);
}

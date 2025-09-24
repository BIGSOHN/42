/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_wall_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:57:03 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/08 14:12:53 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_first_wall(char **map)
{
	int	i;

	i = 0;
	while (map[0][i] != '\0')
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_middle_wall(char **map)
{
	int	i;
	int	j;
	int	line_count;
	int	line_length;

	i = 1;
	line_count = count_map_line(map);
	while (i < line_count - 1)
	{
		line_length = ft_strlen(map[i]);
		if (map[i][0] != '1' || map[i][line_length - 1] != '1')
			return (0);
		j = 1;
		while (j < line_length - 1)
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'P'
			&& map[i][j] != 'E' && map[i][j] != 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_last_wall(char **map)
{
	int	i;
	int	line_count;

	i = 0;
	line_count = count_map_line(map);
	while (map[line_count - 1][i] != '\0')
	{
		if (map[line_count - 1][i] != '1')
			return (0);
		i++;
	}
	return (1);
}

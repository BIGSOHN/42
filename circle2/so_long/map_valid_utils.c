/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:14:53 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/08 14:28:34 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_square(char **map)
{
	int	i;
	int	first_len;
	int	compare_len;
	int	line_count;

	i = 0;
	first_len = ft_strlen(map[0]);
	line_count = count_map_line(map);
	while (i < line_count)
	{
		compare_len = ft_strlen(map[i]);
		if (first_len != compare_len)
			return (0);
		i++;
	}
	return (1);
}

int	is_surround_valid_wall(char **map)
{
	if (check_first_wall(map) == 1
		&& check_middle_wall(map) == 1
		&& check_last_wall(map) == 1)
		return (1);
	return (0);
}

int	is_proper_element(char **map)
{
	int	person_count;
	int	exit_count;
	int	collectible_count;

	person_count = count_person_element(map);
	exit_count = count_exit_element(map);
	collectible_count = count_collectible_element(map);
	if (person_count == 1 && exit_count == 1 && collectible_count >= 1)
		return (1);
	return (0);
}

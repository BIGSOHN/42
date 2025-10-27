/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_element_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 14:41:06 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/07 11:38:03 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_person_element(char **map)
{
	int	i;
	int	j;
	int	person_count;

	i = 0;
	person_count = 0;
	while (i < count_map_line(map))
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'P')
				person_count++;
			j++;
		}
		i++;
	}
	return (person_count);
}

int	count_exit_element(char **map)
{
	int	i;
	int	j;
	int	exit_count;

	i = 0;
	exit_count = 0;
	while (i < count_map_line(map))
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'E')
				exit_count++;
			j++;
		}
		i++;
	}
	return (exit_count);
}

int	count_collectible_element(char **map)
{
	int	i;
	int	j;
	int	collectible_count;

	i = 0;
	collectible_count = 0;
	while (i < count_map_line(map))
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'C')
				collectible_count++;
			j++;
		}
		i++;
	}
	return (collectible_count);
}

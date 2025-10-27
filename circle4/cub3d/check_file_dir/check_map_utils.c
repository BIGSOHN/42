/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:19:55 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/26 19:37:51 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

int	check_map_content(char *map_content)
{
	if (check_map_character(map_content) == 1)
	{
		printf("Error\nInvalid characters found in map\n");
		return (1);
	}
	if (check_split_map(map_content) == 1)
	{
		printf("Error\nMap is disconnected\n");
		return (1);
	}
	return (0);
}

int	check_map_character(char *map_content)
{
	int	word_cnt;
	int	i;
	int	zero_flag;
	int	one_flag;

	i = 0;
	zero_flag = 0;
	one_flag = 0;
	word_cnt = 0;
	while (map_content[i] != '\0')
	{
		if (zero_flag == 0 && map_content[i] == '0')
			zero_flag = 1;
		if (one_flag == 0 && map_content[i] == '1')
			one_flag = 1;
		if (ft_strchr("01NSWE\n ", map_content[i]) == NULL)
			return (1);
		if (ft_strchr("NSWE", map_content[i]) != NULL)
			word_cnt++;
		i++;
	}
	if (one_flag != 1 || word_cnt != 1)
		return (1);
	return (0);
}

int	check_split_map(char *map_content)
{
	int		i;
	int		new_line_flag;
	char	*map_trim;

	i = 0;
	new_line_flag = 0;
	map_trim = ft_strtrim(map_content, "\n");
	while (map_trim[i] != '\0')
	{
		if (map_trim[i] == '\n' && new_line_flag == 0)
			new_line_flag = 1;
		else if (map_trim[i] == '\n' && new_line_flag == 1)
		{
			free(map_trim);
			return (1);
		}
		else if (map_trim[i] != '\n' && new_line_flag == 1)
			new_line_flag = 0;
		i++;
	}
	free(map_trim);
	return (0);
}

int	check_surrounding_cells(t_map_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		j = 0;
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == '0')
			{
				if (check_cell(data, j, i) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_cell(t_map_data *data, int x, int y)
{
	if (data->map[y][x + 1] == '\0')
		return (1);
	if (y == 0 || y == data->map_height - 1)
		return (1);
	if (y + 1 < data->map_height && data->map[y + 1][x] == ' ')
		return (1);
	if (y + 1 < data->map_height && x + 1 < data->map_width
		&& data->map[y + 1][x + 1] == ' ')
		return (1);
	if (y + 1 < data->map_height && x - 1 >= 0
		&& data->map[y + 1][x - 1] == ' ')
		return (1);
	if (y - 1 >= 0 && data->map[y - 1][x] == ' ')
		return (1);
	if (y - 1 >= 0 && x + 1 < data->map_width
		&& data->map[y - 1][x + 1] == ' ')
		return (1);
	if (y - 1 >= 0 && x - 1 >= 0 && data->map[y - 1][x - 1] == ' ')
		return (1);
	if (x + 1 < data->map_width && data->map[y][x + 1] == ' ')
		return (1);
	if (x - 1 >= 0 && data->map[y][x - 1] == ' ')
		return (1);
	return (0);
}

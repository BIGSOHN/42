/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:03:22 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/09 10:55:27 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**make_map(char **argv)
{
	int		fd;
	char	*line;
	char	*full_line;
	char	*temp;
	char	**result;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fail_open_msg_exit(fd);
	line = get_next_line(fd);
	temp = NULL;
	while (line != NULL)
	{
		full_line = ft_strjoin(temp, line);
		free(temp);
		free(line);
		line = get_next_line(fd);
		temp = full_line;
	}
	result = ft_split(full_line, '\n');
	free(full_line);
	close(fd);
	return (result);
}

int	count_input_map_line(char **argv)
{
	char	*line;
	int		input_height;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		fail_open_msg_exit(fd);
	input_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		input_height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (input_height);
}

int	count_map_line(char **map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

int	check_map_valid(char **map, int input_height)
{
	if (map[0] == NULL || is_square(map) != 1
		|| is_surround_valid_wall(map) != 1 || is_proper_element(map) != 1
		|| count_map_line(map) != input_height)
	{
		double_ptr_free(map);
		return (0);
	}
	if (check_path(map) == 0)
		return (0);
	return (1);
}

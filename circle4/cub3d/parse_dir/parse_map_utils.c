/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:45:44 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/17 14:03:05 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	parse_map(t_file_info *info, char *line)
{
	char	*temp;

	temp = info->map_content;
	info->map_content = ft_strjoin(temp, line);
	free(temp);
}

char	**dup_rectangle_map(char **origin_map, int height, int width)
{
	int		i;
	char	**dup_map;

	i = 0;
	dup_map = ft_calloc((height + 1), sizeof(char *));
	if (dup_map == NULL)
		exit(1);
	while (i < height)
	{
		dup_map[i] = dup_map_line(origin_map[i], width);
		i++;
	}
	return (dup_map);
}

char	*dup_map_line(char *line, int width)
{
	char	*dup_line;
	int		i;
	int		len;

	len = ft_strlen(line);
	i = 0;
	dup_line = (char *)malloc(sizeof(char) * width + 1);
	if (dup_line == NULL)
		exit(1);
	ft_memset(dup_line, ' ', width);
	dup_line[width] = '\0';
	while (i < len)
	{
		dup_line[i] = line[i];
		i++;
	}
	return (dup_line);
}

int	count_max_width(char **map)
{
	int	i;
	int	max_len;

	i = 0;
	max_len = 0;
	while (map[i] != NULL)
	{
		if ((int)ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	return (max_len);
}

void	find_player_position(t_map_data *data)
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
			if (ft_strchr("NSWE", data->map[i][j]) != NULL)
			{
				data->p_x = j;
				data->p_y = i;
				data->direction = data->map[i][j];
				data->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

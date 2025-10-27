/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:33:30 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:31:49 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

t_map_data	*convert_info_to_data(t_file_info *info)
{
	t_map_data	*data;
	t_texture	*texture;

	data = ft_calloc(1, sizeof(t_map_data));
	texture = ft_calloc(1, sizeof(t_texture));
	if (data == NULL || texture == NULL)
		exit(1);
	dup_map_setting(info, data);
	dup_texture_setting(info, texture);
	data->texture_data = texture;
	return (data);
}

void	dup_texture_setting(t_file_info *info, t_texture *texture)
{
	texture->no_texture = ft_strdup(info->no_texture);
	texture->so_texture = ft_strdup(info->so_texture);
	texture->we_texture = ft_strdup(info->we_texture);
	texture->ea_texture = ft_strdup(info->ea_texture);
	texture->floor_rgb = parse_rgb_values(info->f_color);
	texture->ceiling_rgb = parse_rgb_values(info->c_color);
}

void	dup_map_setting(t_file_info *info, t_map_data *data)
{
	char	**temp_map;

	temp_map = NULL;
	temp_map = ft_split(info->map_content, '\n');
	data->map_height = ft_word_count(info->map_content, '\n');
	data->map_width = count_max_width(temp_map);
	data->map = dup_rectangle_map(temp_map, data->map_height, data->map_width);
	find_player_position(data);
	double_ptr_free(temp_map);
}

int	parse_rgb_values(char *rgb_str)
{
	char	**rgbs;
	int		red;
	int		green;
	int		blue;
	int		rgb;

	rgbs = ft_split(rgb_str, ',');
	red = ft_atoi(rgbs[0]) << 16;
	green = ft_atoi(rgbs[1]) << 8;
	blue = ft_atoi(rgbs[2]);
	rgb = (red | green | blue);
	double_ptr_free(rgbs);
	return (rgb);
}

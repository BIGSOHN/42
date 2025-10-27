/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:45:36 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:32:07 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	parse_texture(t_file_info *info, char *line)
{
	count_textures_key(info, line);
	if (info->no_texture == NULL && ft_strncmp(line, "NO ", 3) == 0)
		info->no_texture = input_texture(line);
	else if (info->so_texture == NULL && ft_strncmp(line, "SO ", 3) == 0)
		info->so_texture = input_texture(line);
	else if (info->we_texture == NULL && ft_strncmp(line, "WE ", 3) == 0)
		info->we_texture = input_texture(line);
	else if (info->ea_texture == NULL && ft_strncmp(line, "EA ", 3) == 0)
		info->ea_texture = input_texture(line);
	else if (info->f_color == NULL && ft_strncmp(line, "F ", 2) == 0)
		info->f_color = set_rgb(line);
	else if (info->c_color == NULL && ft_strncmp(line, "C ", 2) == 0)
		info->c_color = set_rgb(line);
	else if (ft_strncmp(line, "\n", 2) == 0)
		return ;
	else
		info->error_flag = 1;
	check_textures_set(info);
}

void	check_textures_set(t_file_info *info)
{
	if (info->c_color != NULL && info->f_color != NULL \
		&& info->ea_texture != NULL && info->no_texture != NULL \
		&& info->so_texture != NULL && info->we_texture != NULL)
		info->full_flag = 1;
}

char	*input_texture(char *sub_line)
{
	char	**temps;
	char	*trim_str;
	char	*data;

	trim_str = ft_strtrim(sub_line, "\n");
	if (ft_word_count(trim_str, ' ') != 2)
	{
		free(trim_str);
		return (NULL);
	}
	temps = ft_split(trim_str, ' ');
	data = ft_strdup(temps[1]);
	double_ptr_free(temps);
	free(trim_str);
	return (data);
}

char	*set_rgb(char *sub_line)
{
	char	*rgb_str;
	char	*trim_str;
	int		len;

	trim_str = ft_strtrim(sub_line, "\n");
	len = ft_strlen(ft_strchr(trim_str, ' ') + 1);
	rgb_str = ft_substr(trim_str, ft_strlen(trim_str) - len, len);
	if (ft_word_count(rgb_str, ',') != 3)
	{
		free(trim_str);
		free(rgb_str);
		return (NULL);
	}
	free(trim_str);
	return (rgb_str);
}

void	count_textures_key(t_file_info *info, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 \
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		info->count_settings++;
}

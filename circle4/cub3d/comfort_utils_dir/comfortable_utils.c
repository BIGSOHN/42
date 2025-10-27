/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comfortable_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:11:50 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:29:54 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	print_file_info(t_file_info *info)
{
	printf("=====print_file_info=====\n");
	printf("no :%s", info->no_texture);
	printf("so :%s", info->so_texture);
	printf("we :%s", info->we_texture);
	printf("ea :%s", info->ea_texture);
	printf("floor rgb :%s", info->f_color);
	printf("ceiling rgb :%s", info->c_color);
	printf("map str :%s\n", info->map_content);
	printf("flag :%d\n", info->full_flag);
	printf("count :%d\n", info->count_settings);
}

void	print_data(t_map_data *data)
{
	int			i;
	t_texture	*texture;

	i = 0;
	texture = data->texture_data;
	printf("=====print_data=====\n");
	printf("height :%d\n", data->map_height);
	printf("width : %d\n", data->map_width);
	printf("p_x: %d\tp_y :%d\n", data->p_x, data->p_y);
	printf("p_direction: %d\n", data->direction);
	printf("no :%s\n", texture->no_texture);
	printf("so :%s\n", texture->so_texture);
	printf("we :%s\n", texture->we_texture);
	printf("ea :%s\n", texture->ea_texture);
	printf("floor rgb :%d\n", texture->floor_rgb);
	printf("ceiling rgb :%d\n", texture->ceiling_rgb);
	printf("map :\n");
	while (data->map[i] != NULL)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
}

int	ft_word_count(char const *s, char c)
{
	int	count;
	int	i;
	int	len;

	count = 0;
	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if (((s[i] == c && len > 0) || (s[i] != c && s[i + 1] == '\0')))
		{
			len = 0;
			count++;
		}
		if (s[i] != c)
			len++;
		i++;
	}
	return (count);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:02:43 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:30:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

void	double_ptr_free(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_file_info(t_file_info *info)
{
	if (info == NULL)
		return ;
	if (info->no_texture != NULL)
		free(info->no_texture);
	if (info->so_texture != NULL)
		free(info->so_texture);
	if (info->we_texture != NULL)
		free(info->we_texture);
	if (info->ea_texture != NULL)
		free(info->ea_texture);
	if (info->f_color != NULL)
		free(info->f_color);
	if (info->c_color != NULL)
		free(info->c_color);
	if (info->map_content != NULL)
		free(info->map_content);
	free(info);
}

void	free_texture(t_texture *texture)
{
	if (texture == NULL)
		return ;
	if (texture->no_texture != NULL)
		free(texture->no_texture);
	if (texture->so_texture != NULL)
		free(texture->so_texture);
	if (texture->we_texture != NULL)
		free(texture->we_texture);
	if (texture->ea_texture != NULL)
		free(texture->ea_texture);
	free(texture);
}

void	free_map_data(t_map_data *data)
{
	if (data == NULL)
		return ;
	free_texture(data->texture_data);
	if (data->map != NULL)
		double_ptr_free(data->map);
	free(data);
}

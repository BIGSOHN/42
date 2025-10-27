/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:42:19 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/02 18:28:07 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_pixel(t_game *game, char map_element, int width, int height)
{
	if (map_element == '0')
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->g, width, height);
	if (map_element == '1')
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->w, width, height);
	if (map_element == 'P')
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->p, width, height);
	if (map_element == 'E')
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->e, width, height);
	if (map_element == 'C')
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->c, width, height);
}

void	draw_map(t_game *game)
{
	int			i;
	int			j;
	int			width;
	int			height;
	t_map_info	*map_info;

	i = 0;
	height = 0;
	map_info = game->map_info;
	while (i < map_info->map_height)
	{
		j = 0;
		width = 0;
		while (j < map_info->map_width)
		{
			draw_pixel(game, map_info->map[i][j], width, height);
			j++;
			width = width + IMG_WDTH;
		}
		i++;
		height = height + IMG_HGHT;
	}
}

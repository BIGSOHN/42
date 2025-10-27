/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 07:56:13 by esong             #+#    #+#             */
/*   Updated: 2025/02/26 20:06:04 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_img img, t_map map)
{
	int	i;
	int	j;
	int	color;

	j = 0;
	color = map.ceiling_rgb;
	while (j < WIN_HEIGHT)
	{
		i = 0;
		if (j == WIN_HEIGHT / 2)
			color = map.floor_rgb;
		while (i < WIN_WIDTH)
		{
			cub3d_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
}

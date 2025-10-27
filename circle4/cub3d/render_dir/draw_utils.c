/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:36:25 by esong             #+#    #+#             */
/*   Updated: 2025/02/19 20:25:53 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_map map, double x, double y)
{
	int	index_x;
	int	index_y;

	index_x = (int)x / CELL_SIZE;
	index_y = (int)y / CELL_SIZE;
	if (map.map[index_y][index_x] == WALL)
		return (1);
	return (0);
}

void	cub3d_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if ((x >= 0 && x <= WIN_WIDTH) && (y >= 0 && y <= WIN_HEIGHT))
	{
		dst = img.addr + (y * img.size_line + x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

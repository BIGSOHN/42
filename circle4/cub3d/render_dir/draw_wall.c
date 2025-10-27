/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 07:50:45 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 17:09:00 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	calculate_wall_height(t_hit_info hit_info, double angle);
static int		calculate_img_index_x(t_map map, t_hit_info hit, int wall);

void	draw_wall_height(t_img img, t_draw draw, int x)
{
	int		i;
	int		img_y;

	i = 0;
	if (draw.start_wall < 0)
		i = -1 * draw.start_wall;
	while (i < draw.wall_height)
	{
		img_y = i * (draw.wall_img.height / draw.wall_height);
		cub3d_pixel_put(img, x, draw.start_wall + i, \
			draw.img_addr[img_y * draw.wall_img.height + draw.img_x]);
		if (draw.start_wall + i >= WIN_HEIGHT)
			break ;
		i++;
	}
}

t_draw	setting_draw_info(t_map map, t_hit_info hit_info, double angle)
{
	t_draw	draw;

	draw.wall_img = map.wall[hit_info.hit_wall];
	draw.img_addr = (unsigned int *)map.wall[hit_info.hit_wall].addr;
	draw.wall_height = calculate_wall_height(hit_info, angle);
	draw.start_wall = (WIN_HEIGHT - draw.wall_height) / 2;
	draw.img_x = calculate_img_index_x(map, hit_info, hit_info.hit_wall);
	return (draw);
}

static double	calculate_wall_height(t_hit_info hit_info, double angle)
{
	double	camera_to_wall;
	double	wall_height;

	camera_to_wall = sin((PI / 3) + angle) * hit_info.dist_ray;
	wall_height = (WIN_HEIGHT / camera_to_wall) * 30;
	return (wall_height);
}

static int	calculate_img_index_x(t_map map, t_hit_info hit, int wall)
{
	double	hit_pos;
	double	img_width;
	int		img_index_x;

	if (wall == E || wall == W)
		hit_pos = hit.hit_y;
	else
		hit_pos = hit.hit_x;
	img_width = map.wall[wall].width;
	if (wall == E || wall == S)
		img_index_x = (CELL_SIZE - fmod(hit_pos, CELL_SIZE)) * \
			(img_width / CELL_SIZE);
	else
		img_index_x = fmod(hit_pos, CELL_SIZE) * \
			(img_width / CELL_SIZE);
	return (img_index_x);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 07:48:08 by esong             #+#    #+#             */
/*   Updated: 2025/02/26 20:07:00 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_one_ray(t_map *map, t_ray *ray, t_user user);
static void	setting_hit_info(t_dda_info dda, t_ray *ray, t_user user);

void	cast_ray_fov(t_map *map, t_img img, t_user user, t_ray *ray)
{
	int		i;
	t_draw	draw;

	i = 0;
	setting_angle(ray);
	while (i < WIN_WIDTH)
	{
		cast_one_ray(map, ray, user);
		draw = setting_draw_info(*map, ray->hit_info, ray->step_angle * i);
		draw_wall_height(img, draw, i);
		ray->rot_angle += ray->step_angle;
		i++;
	}
}

static void	cast_one_ray(t_map *map, t_ray *ray, t_user user)
{
	t_point		pos;
	t_dda_info	dda;

	pos.x = user.x;
	pos.y = user.y;
	setting_ray_direction(ray, user, ray->rot_angle);
	setting_dda_info(&dda, *ray, user);
	while (dda.hit_side == 0)
	{
		if (dda.dist_hit_x < dda.dist_hit_y)
			dda.hit_side = move_x(&dda, *map, &pos);
		else
			dda.hit_side = move_y(&dda, *map, &pos);
	}
	setting_hit_info(dda, ray, user);
}

static void	setting_hit_info(t_dda_info dda, t_ray *ray, t_user user)
{
	if (dda.hit_side == 'x')
	{
		if (dda.step_x == 1)
			ray->hit_info.hit_wall = W;
		else if (dda.step_x == -1)
			ray->hit_info.hit_wall = E;
		ray->hit_info.dist_ray = dda.dist_hit_x - dda.dist_grid_x;
	}
	else
	{
		if (dda.step_y == 1)
			ray->hit_info.hit_wall = S;
		else if (dda.step_y == -1)
			ray->hit_info.hit_wall = N;
		ray->hit_info.dist_ray = dda.dist_hit_y - dda.dist_grid_y;
	}
	ray->hit_info.hit_x = user.x + (ray->dir_x * ray->hit_info.dist_ray);
	ray->hit_info.hit_y = user.y + (ray->dir_y * ray->hit_info.dist_ray);
}

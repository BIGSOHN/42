/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:36:39 by esong             #+#    #+#             */
/*   Updated: 2025/02/26 20:08:51 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setting_angle(t_ray *ray)
{
	double	fov;

	fov = PI / 3;
	ray->rot_angle = -(fov / 2);
	ray->step_angle = fov / WIN_WIDTH;
}

void	setting_ray_direction(t_ray *ray, t_user user, double rot_angle)
{
	ray->dir_x = user.dir_x * cos(rot_angle) - user.dir_y * sin(rot_angle);
	ray->dir_y = user.dir_x * sin(rot_angle) + user.dir_y * cos(rot_angle);
}

void	setting_dda_info(t_dda_info *dda, t_ray ray, t_user user)
{
	dda->hit_side = 0;
	dda->dist_grid_x = sqrt(pow(ray.dir_y / ray.dir_x, 2) + 1);
	dda->dist_grid_y = sqrt(pow(ray.dir_x / ray.dir_y, 2) + 1);
	if (ray.dir_x > 0)
	{
		dda->dist_hit_x = ((int)user.x + 1 - user.x) * dda->dist_grid_x;
		dda->step_x = 1;
	}
	else
	{
		dda->dist_hit_x = (user.x - (int)user.x) * dda->dist_grid_x;
		dda->step_x = -1;
	}
	if (ray.dir_y > 0)
	{
		dda->dist_hit_y = ((int)user.y + 1 - user.y) * dda->dist_grid_y;
		dda->step_y = 1;
	}
	else
	{
		dda->dist_hit_y = (user.y - (int)user.y) * dda->dist_grid_y;
		dda->step_y = -1;
	}
}

char	move_x(t_dda_info *dda, t_map map, t_point *pos)
{
	pos->x += dda->step_x;
	dda->dist_hit_x += dda->dist_grid_x;
	if (is_wall(map, pos->x, pos->y) == TRUE)
		return ('x');
	return (0);
}

char	move_y(t_dda_info *dda, t_map map, t_point *pos)
{
	pos->y += dda->step_y;
	dda->dist_hit_y += dda->dist_grid_y;
	if (is_wall(map, pos->x, pos->y) == TRUE)
		return ('y');
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:42:04 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 11:26:01 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_view(int key, t_user *user);
static void	move_user(int key, t_map *map, t_user *user);
static void	setting_dir(t_user user, int key, double *dir_x, double *dir_y);
static void	re_rendering(t_cub3d *cub3d);

int	key_handler(int key, t_cub3d *cub3d)
{
	if (key == KEY_ESC)
		end_program(cub3d);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		rotate_view(key, &cub3d->user);
	else if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D)
		move_user(key, &cub3d->map, &cub3d->user);
	re_rendering(cub3d);
	return (0);
}

static void	rotate_view(int key, t_user *user)
{
	double	rot_x;
	double	rot_y;
	double	rot_angle;

	rot_angle = PI / 36;
	if (key == KEY_RIGHT)
	{
		rot_x = user->dir_x * cos(rot_angle) - user->dir_y * sin(rot_angle);
		rot_y = user->dir_x * sin(rot_angle) + user->dir_y * cos(rot_angle);
	}
	else
	{
		rot_x = user->dir_x * cos(-rot_angle) - user->dir_y * sin(-rot_angle);
		rot_y = user->dir_x * sin(-rot_angle) + user->dir_y * cos(-rot_angle);
	}
	user->dir_x = rot_x;
	user->dir_y = rot_y;
}

static void	move_user(int key, t_map *map, t_user *user)
{
	double	dir_x;
	double	dir_y;
	int		i;

	i = 0;
	while (i < MV_STEP)
	{
		setting_dir(*user, key, &dir_x, &dir_y);
		if (is_wall(*map, user->x + dir_x * 2, user->y + dir_y * 2) == TRUE)
			break ;
		user->x += dir_x;
		user->y += dir_y;
		i++;
	}
}

static void	setting_dir(t_user user, int key, double *dir_x, double *dir_y)
{
	if (key == KEY_W)
	{
		*dir_x = user.dir_x;
		*dir_y = user.dir_y;
	}
	else if (key == KEY_S)
	{
		*dir_x = (-1) * user.dir_x;
		*dir_y = (-1) * user.dir_y;
	}
	else if (key == KEY_D)
	{
		*dir_x = (-1) * user.dir_y;
		*dir_y = user.dir_x;
	}
	else if (key == KEY_A)
	{
		*dir_x = user.dir_y;
		*dir_y = (-1) * user.dir_x;
	}
}

static void	re_rendering(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->img.img);
	setup_img(&cub3d->mlx, &cub3d->img);
	rendering(*cub3d);
}

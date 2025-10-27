/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 05:54:22 by esong             #+#    #+#             */
/*   Updated: 2025/02/27 15:33:50 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	setup_map_info(t_mlx mlx, t_map *map, t_map_data data);
static void	setup_user_info(t_user *user, t_map_data data);
static int	setup_window(t_mlx *mlx, t_img *img);

void	setup_cub3d(t_cub3d *cub3d, t_map_data *data)
{
	if (setup_map_info(cub3d->mlx, &cub3d->map, *data) == 1)
		config_error(cub3d);
	setup_user_info(&cub3d->user, *data);
	setup_window(&cub3d->mlx, &cub3d->img);
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, &key_handler, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, &end_program, cub3d);
}

static int	setup_map_info(t_mlx mlx, t_map *map, t_map_data data)
{
	map->map = data.map;
	map->map_height = data.map_height;
	map->map_width = data.map_width;
	map->floor_rgb = data.texture_data->floor_rgb;
	map->ceiling_rgb = data.texture_data->ceiling_rgb;
	if (setup_wall_texture(mlx, map, *data.texture_data) == 1)
		return (1);
	return (0);
}

static void	setup_user_info(t_user *user, t_map_data data)
{
	user->x = (data.p_x * CELL_SIZE) + (CELL_SIZE / 2);
	user->y = (data.p_y * CELL_SIZE) + (CELL_SIZE / 2);
	setup_user_direction(user, data.direction);
}

static int	setup_window(t_mlx *mlx, t_img *img)
{
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (mlx->win == NULL)
		return (1);
	if (setup_img(mlx, img) == 1)
		return (1);
	return (0);
}

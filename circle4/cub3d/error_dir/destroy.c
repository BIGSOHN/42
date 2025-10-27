/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:28:16 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 18:34:42 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_texture_img(void *mlx_ptr, t_map *map);

int	end_program(t_cub3d *cub3d)
{
	destroy_before_end(cub3d);
	exit(0);
	return (0);
}

void	destroy_before_end(t_cub3d *cub3d)
{
	free_map_data(cub3d->data);
	destroy_texture_img(cub3d->mlx.mlx, &cub3d->map);
	if (cub3d->img.img != NULL)
		mlx_destroy_image(cub3d->mlx.mlx, cub3d->img.img);
	if (cub3d->mlx.mlx != NULL && cub3d->mlx.win != NULL)
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	if (cub3d->mlx.mlx != NULL)
	{
		mlx_destroy_display(cub3d->mlx.mlx);
		free(cub3d->mlx.mlx);
	}
}

static void	destroy_texture_img(void *mlx_ptr, t_map *map)
{
	if (map->wall[E].img != NULL)
		mlx_destroy_image(mlx_ptr, map->wall[E].img);
	if (map->wall[W].img != NULL)
		mlx_destroy_image(mlx_ptr, map->wall[W].img);
	if (map->wall[S].img != NULL)
		mlx_destroy_image(mlx_ptr, map->wall[S].img);
	if (map->wall[N].img != NULL)
		mlx_destroy_image(mlx_ptr, map->wall[N].img);
}

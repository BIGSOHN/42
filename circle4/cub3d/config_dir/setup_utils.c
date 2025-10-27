/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 06:21:28 by esong             #+#    #+#             */
/*   Updated: 2025/02/24 10:35:14 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	xpm_to_img(t_mlx mlx, t_img *img, char *file);

int	setup_wall_texture(t_mlx mlx, t_map *map, t_texture texture)
{
	if (xpm_to_img(mlx, &map->wall[E], texture.ea_texture) == 1)
		return (1);
	if (xpm_to_img(mlx, &map->wall[W], texture.we_texture) == 1)
		return (1);
	if (xpm_to_img(mlx, &map->wall[S], texture.so_texture) == 1)
		return (1);
	if (xpm_to_img(mlx, &map->wall[N], texture.no_texture) == 1)
		return (1);
	return (0);
}

void	setup_user_direction(t_user *user, char direction)
{
	if (direction == 'E')
		user->dir_x = 1;
	else if (direction == 'W')
		user->dir_x = -1;
	else if (direction == 'S')
		user->dir_y = 1;
	else if (direction == 'N')
		user->dir_y = -1;
}

int	setup_img(t_mlx *mlx, t_img *img)
{
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (img->img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->size_line, &img->endian);
	if (img->addr == NULL)
		return (1);
	return (0);
}

static int	xpm_to_img(t_mlx mlx, t_img *img, char *file)
{
	img->img = mlx_xpm_file_to_image(mlx.mlx, file, &img->width, &img->height);
	if (img->img == NULL)
		return (1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->size_line, &img->endian);
	return (0);
}

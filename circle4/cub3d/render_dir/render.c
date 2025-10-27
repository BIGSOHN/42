/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 07:57:05 by esong             #+#    #+#             */
/*   Updated: 2025/02/26 20:08:45 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rendering(t_cub3d cub3d)
{
	draw_background(cub3d.img, cub3d.map);
	cast_ray_fov(&cub3d.map, cub3d.img, cub3d.user, &cub3d.ray);
	mlx_put_image_to_window(cub3d.mlx.mlx, cub3d.mlx.win, cub3d.img.img, 0, 0);
}

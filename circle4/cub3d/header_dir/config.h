/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:47:34 by esong             #+#    #+#             */
/*   Updated: 2025/02/24 10:31:31 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "cub3d.h"
# include "cub3d_types.h"

//init.c
void	init_cub3d(t_cub3d *cub3d, t_map_data *data);
//setup.c
void	setup_cub3d(t_cub3d *cub3d, t_map_data *data);
//setup_utils.c
void	setup_user_direction(t_user *user, char direction);
int		setup_wall_texture(t_mlx mlx, t_map *map, t_texture texture);
int		setup_img(t_mlx *mlx, t_img *img);
//key_handler.c
int		key_handler(int key, t_cub3d *cub3d);

#endif
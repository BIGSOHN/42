/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:18:02 by esong             #+#    #+#             */
/*   Updated: 2025/02/26 20:07:29 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"
# include "cub3d_types.h"

// render.c
void	rendering(t_cub3d cub3d);
//raycasting.c
void	cast_ray_fov(t_map *map, t_img img, t_user user, t_ray *ray);
//raycasting_utils.c
void	setting_angle(t_ray *ray);
void	setting_ray_direction(t_ray *ray, t_user user, double rot_angle);
void	setting_dda_info(t_dda_info *dda, t_ray ray, t_user user);
char	move_x(t_dda_info *dda, t_map map, t_point *pos);
char	move_y(t_dda_info *dda, t_map map, t_point *pos);
//draw_background.c
void	draw_background(t_img img, t_map map);
//draw_wall.c
void	draw_wall_height(t_img img, t_draw draw, int x);
t_draw	setting_draw_info(t_map map, t_hit_info hit_info, double angle);
//draw_utils.c
int		is_wall(t_map map, double x, double y);
void	cub3d_pixel_put(t_img img, int x, int y, int color);

#endif
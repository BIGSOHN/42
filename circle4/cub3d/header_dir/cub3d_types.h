/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:40:45 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/27 10:10:57 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_TYPES_H
# define CUB3D_TYPES_H

typedef struct s_file_info
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*f_color;
	char	*c_color;
	char	*map_content;
	int		full_flag;
	int		error_flag;
	int		count_settings;
}t_file_info;

typedef struct s_texture
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_rgb;
	int		ceiling_rgb;
}t_texture;

typedef struct s_map_data
{
	char		**map;
	int			map_height;
	int			map_width;
	int			p_x;
	int			p_y;
	char		direction;
	t_texture	*texture_data;
}t_map_data;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;
	int			floor_rgb;
	int			ceiling_rgb;
	t_img		wall[4];
}	t_map;

typedef struct s_user
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
}	t_user;

typedef struct s_dda_info
{
	double		dist_hit_x;
	double		dist_hit_y;
	double		dist_grid_x;
	double		dist_grid_y;
	int			step_x;
	int			step_y;
	int			hit_side;
}	t_dda_info;

typedef struct s_hit_info
{
	double			hit_x;
	double			hit_y;
	int				hit_wall;
	double			dist_ray;
}	t_hit_info;

typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	double		rot_angle;
	double		step_angle;
	t_hit_info	hit_info;
}	t_ray;

typedef struct s_draw
{
	t_img			wall_img;
	unsigned int	*img_addr;
	int				img_x;
	double			wall_height;
	double			start_wall;
}	t_draw;

typedef struct s_cub3d
{
	t_mlx			mlx;
	t_img			img;
	t_map			map;
	t_user			user;
	t_ray			ray;
	t_map_data		*data;
}	t_cub3d;

#endif

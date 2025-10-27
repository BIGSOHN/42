/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 21:49:17 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/26 17:21:08 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "cub3d.h"
# include "cub3d_types.h"

//parse_data_utils.c
t_map_data	*convert_info_to_data(t_file_info *info);
void		dup_texture_setting(t_file_info *info, t_texture *texture);
void		dup_map_setting(t_file_info *info, t_map_data *data);
int			parse_rgb_values(char *rgb_str);
//parse_fail_msg.c
void		fail_proper_argument_msg_exit(void);
void		fail_valid_file_exetension_msg_exit(void);
void		fail_open_msg_exit(void);
//parse_file_utils.c
int			parse_info(t_file_info *info, char *line);
t_file_info	*parse_scene_config(int argc, char **argv);
//parse_map_utils.c
void		parse_map(t_file_info *info, char *line);
char		**dup_rectangle_map(char **origin_map, int height, int width);
char		*dup_map_line(char *line, int width);
int			count_max_width(char **map);
void		find_player_position(t_map_data *data);
//parse_textures_utils.c
void		parse_texture(t_file_info *info, char *line);
void		check_textures_set(t_file_info *info);
char		*input_texture(char *sub_line);
char		*set_rgb(char *sub_line);
void		count_textures_key(t_file_info *info, char *line);
//prepare.c
t_map_data	*prepare_cub3d(int argc, char **argv);

#endif

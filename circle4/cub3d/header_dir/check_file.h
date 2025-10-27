/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:31:37 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:30:31 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_FILE_H
# define CHECK_FILE_H

# include "cub3d.h"
# include "cub3d_types.h"

//check_color_utils.c
int	validate_floor_ceiling_rgb(t_file_info	*info);
int	check_rgb_code_character(char *all_rgb);
int	validate_rgb(char *all_rgb);
int	is_valid_number_string(char	*nptr);

//check_file_utils.c
int	check_valid_file_exetension(char **argv);
int	open_scene_file(int argc, char **argv);
int	check_file_info(t_file_info	*info);

//check_map_utils.h
int	check_map_content(char *map_content);
int	check_map_character(char *map_content);
int	check_split_map(char *map_content);
int	check_surrounding_cells(t_map_data *data);
int	check_cell(t_map_data *data, int x, int y);

#endif

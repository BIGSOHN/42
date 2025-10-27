/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comfort_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:36:20 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/25 10:30:37 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMFORT_UTILS_H
# define COMFORT_UTILS_H

# include "cub3d.h"
# include "cub3d_types.h"

//comfortable_utils.c
void	print_file_info(t_file_info *info);
void	print_data(t_map_data *data);
int		ft_word_count(char const *s, char c);

//free_utils.c
void	double_ptr_free(char **str);
void	free_file_info(t_file_info *info);
void	free_texture(t_texture *texture);
void	free_map_data(t_map_data *data);

#endif

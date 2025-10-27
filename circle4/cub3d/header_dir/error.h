/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esong <esong@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:03:34 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 11:27:38 by esong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "cub3d.h"
# include "cub3d_types.h"

// erorr.c
void	config_error(t_cub3d *cub3d);
// destroy.c
int		end_program(t_cub3d *cub3d);
void	destroy_before_end(t_cub3d *cub3d);

#endif

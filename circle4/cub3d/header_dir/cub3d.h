/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:35:38 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 10:48:04 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1010
# define WALL '1'
# define PI 3.141592
# define MV_STEP 3
# define TRUE 1
# define FALSE 0
# define E 0
# define W 1
# define S 2
# define N 3
# define CELL_SIZE 20

// key (mlx_linux)
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# include "libft.h"
# include "comfort_utils.h"
# include "check_file.h"
# include "parse.h"
# include "config.h"
# include "render.h"
# include "error.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

#endif

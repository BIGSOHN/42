/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:01:19 by esong             #+#    #+#             */
/*   Updated: 2025/02/27 15:27:18 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx(t_mlx *mlx);

void	init_cub3d(t_cub3d *cub3d, t_map_data *data)
{
	ft_memset(cub3d, 0, sizeof(t_cub3d));
	cub3d->data = data;
	if (init_mlx(&cub3d->mlx) == 1)
		config_error(cub3d);
}

static int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	if (mlx->mlx == NULL)
		return (1);
	return (0);
}

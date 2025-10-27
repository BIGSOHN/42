/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:35:32 by esong             #+#    #+#             */
/*   Updated: 2025/02/25 10:31:35 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map_data	*data;
	t_cub3d		cub3d;

	data = prepare_cub3d(argc, argv);
	if (data == NULL)
		return (0);
	init_cub3d(&cub3d, data);
	setup_cub3d(&cub3d, data);
	rendering(cub3d);
	mlx_loop(cub3d.mlx.mlx);
}

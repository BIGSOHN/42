/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:37:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/08 09:38:10 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*init_game_map(void)
{
	t_game		*game_map;
	t_map_info	*map_info;

	game_map = malloc(sizeof(t_game));
	if (game_map == NULL)
		exit(0);
	map_info = malloc(sizeof(t_map_info));
	if (map_info == NULL)
		exit(0);
	ft_memset(game_map, 0, sizeof(t_game));
	ft_memset(map_info, 0, sizeof(t_map_info));
	game_map->map_info = map_info;
	return (game_map);
}

void	set_param(t_game *game, char **input_map)
{
	t_map_info	*info;
	int			h;
	int			w;

	h = IMG_HGHT;
	w = IMG_WDTH;
	info = game->map_info;
	info->map = input_map;
	info->collectible_count = count_collectible_element(info->map);
	info->map_width = ft_strlen(game->map_info->map[0]);
	info->map_height = count_map_line(game->map_info->map);
	game->mlx_ptr = mlx_init();
	game->window_ptr = mlx_new_window(game->mlx_ptr,
			info->map_width * IMG_WDTH, info->map_height * IMG_HGHT, "so_long");
	game->g = mlx_xpm_file_to_image(game->mlx_ptr, "images/0.xpm", &w, &h);
	game->w = mlx_xpm_file_to_image(game->mlx_ptr, "images/1.xpm", &w, &h);
	game->p = mlx_xpm_file_to_image(game->mlx_ptr, "images/P_D.xpm", &w, &h);
	game->c = mlx_xpm_file_to_image(game->mlx_ptr, "images/C.xpm", &w, &h);
	game->e = mlx_xpm_file_to_image(game->mlx_ptr, "images/E.xpm", &w, &h);
	find_person_pos(game, info->map);
}

void	find_person_pos(t_game *game, char **input_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < count_map_line(input_map))
	{
		x = 0;
		while (input_map[y][x] != '\0')
		{
			if (input_map[y][x] == 'P')
			{
				game->pos_x = x;
				game->pos_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	release_game(t_game *game)
{
	mlx_destroy_display(game->mlx_ptr);
}

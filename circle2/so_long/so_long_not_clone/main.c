/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 10:30:24 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/12 12:55:09 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	*game;
	char	**input_map;

	check_file_and_parsing(argc, argv);
	input_map = make_map(argv);
	game = init_game_map();
	set_param(game, input_map);
	draw_map(game);
	mlx_hook(game->window_ptr, PRESS_KEY, 1L << 0, &press_key_event, game);
	mlx_hook(game->window_ptr, PRESS_X_BUTTON, 0L, &event_end_game, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}

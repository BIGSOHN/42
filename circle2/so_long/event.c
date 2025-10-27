/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:07:01 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/08 14:57:19 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	press_key_event(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		move_up(game, game->map_info);
	if (key_code == KEY_A)
		move_left(game, game->map_info);
	if (key_code == KEY_S)
		move_down(game, game->map_info);
	if (key_code == KEY_D)
		move_right(game, game->map_info);
	if (key_code == KEY_ESC)
		event_end_game(game);
	return (0);
}

int	event_end_game(t_game *game)
{
	ft_printf("The end\n");
	double_ptr_free(game->map_info->map);
	free(game->map_info);
	mlx_loop_end(game->mlx_ptr);
	mlx_destroy_image(game->mlx_ptr, game->g);
	mlx_destroy_image(game->mlx_ptr, game->w);
	mlx_destroy_image(game->mlx_ptr, game->p);
	mlx_destroy_image(game->mlx_ptr, game->c);
	mlx_destroy_image(game->mlx_ptr, game->e);
	mlx_clear_window(game->mlx_ptr, game->window_ptr);
	mlx_destroy_window(game->mlx_ptr, game->window_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	free(game);
	exit(0);
	return (0);
}

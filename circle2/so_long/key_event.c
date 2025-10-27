/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:14:23 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/08 14:58:34 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game, t_map_info *info)
{
	if ((info->map[game->pos_y - 1][game->pos_x] == '1')
	|| (info->map[game->pos_y - 1][game->pos_x] == 'E'
	&& info->collectible_count != 0))
		return ;
	else
	{
		game->move_count++;
		ft_printf("move count : %d\n", game->move_count);
		if (info->map[game->pos_y - 1][game->pos_x] == 'E')
		{
			ft_printf("Win The Game!!!\n");
			event_end_game(game);
		}
		if (info->map[game->pos_y - 1][game->pos_x] == 'C')
			info->collectible_count--;
		info->map[game->pos_y - 1][game->pos_x] = 'P';
		info->map[game->pos_y][game->pos_x] = '0';
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->g, game->pos_x * 64, game->pos_y * 64);
		game->pos_y--;
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->p, game->pos_x * 64, game->pos_y * 64);
	}
}

void	move_down(t_game *game, t_map_info *info)
{
	if ((info->map[game->pos_y + 1][game->pos_x] == '1')
	|| (info->map[game->pos_y + 1][game->pos_x] == 'E'
	&& info->collectible_count != 0))
		return ;
	else
	{
		game->move_count++;
		ft_printf("move count : %d\n", game->move_count);
		if (info->map[game->pos_y + 1][game->pos_x] == 'E')
		{
			ft_printf("Win The Game!!!\n");
			event_end_game(game);
		}
		if (info->map[game->pos_y + 1][game->pos_x] == 'C')
			info->collectible_count--;
		info->map[game->pos_y + 1][game->pos_x] = 'P';
		info->map[game->pos_y][game->pos_x] = '0';
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->g, game->pos_x * 64, game->pos_y * 64);
		game->pos_y++;
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->p, game->pos_x * 64, game->pos_y * 64);
	}
}

void	move_right(t_game *game, t_map_info *info)
{
	if ((info->map[game->pos_y][game->pos_x + 1] == '1')
	|| (info->map[game->pos_y][game->pos_x + 1] == 'E'
	&& info->collectible_count != 0))
		return ;
	else
	{
		game->move_count++;
		ft_printf("move count : %d\n", game->move_count);
		if (info->map[game->pos_y][game->pos_x + 1] == 'E')
		{
			ft_printf("Win The Game!!!\n");
			event_end_game(game);
		}
		if (info->map[game->pos_y][game->pos_x + 1] == 'C')
			info->collectible_count--;
		info->map[game->pos_y][game->pos_x + 1] = 'P';
		info->map[game->pos_y][game->pos_x] = '0';
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->g, game->pos_x * 64, game->pos_y * 64);
		game->pos_x++;
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->p, game->pos_x * 64, game->pos_y * 64);
	}
}

void	move_left(t_game *game, t_map_info *info)
{
	if ((info->map[game->pos_y][game->pos_x - 1] == '1')
	|| (info->map[game->pos_y][game->pos_x - 1] == 'E'
	&& info->collectible_count != 0))
		return ;
	else
	{
		game->move_count++;
		ft_printf("move count : %d\n", game->move_count);
		if (info->map[game->pos_y][game->pos_x - 1] == 'E')
		{
			ft_printf("Win The Game!!!\n");
			event_end_game(game);
		}
		if (info->map[game->pos_y][game->pos_x - 1] == 'C')
			info->collectible_count--;
		info->map[game->pos_y][game->pos_x - 1] = 'P';
		info->map[game->pos_y][game->pos_x] = '0';
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->g, game->pos_x * 64, game->pos_y * 64);
		game->pos_x--;
		mlx_put_image_to_window(game->mlx_ptr, game->window_ptr,
			game->p, game->pos_x * 64, game->pos_y * 64);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 13:06:46 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/12 11:15:14 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include <stddef.h>
# include <stdio.h>

# define IMG_HGHT 64
# define IMG_WDTH 64
# define PRESS_KEY 2
# define PRESS_X_BUTTON 17
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

typedef struct s_map_info
{
	char	**map;
	int		map_height;
	int		map_width;
	int		collectible_count;
}t_map_info;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*window_ptr;
	void		*g;
	void		*w;
	void		*p;
	void		*e;
	void		*c;
	int			pos_x;
	int			pos_y;
	int			move_count;
	t_map_info	*map_info;
}t_game;

typedef struct s_path
{
	char	**map;
	int		valid_path;
	int		pos_x;
	int		pos_y;
	int		collect;
}t_path;

//main.c
int		main(int argc, char **argv);
//map_utils.c
char	**make_map(char **argv);
int		count_input_map_line(char **argv);
int		count_map_line(char **map);
int		check_map_valid(char **map, int input_height);
//error_msg.c
void	fail_proper_argument_msg_exit(void);
void	fail_open_msg_exit(int fd);
void	fail_map_valid_msg_exit_free(void);
void	fail_valid_file_exetension_msg_exit(void);
void	fail_file_is_empty_msg_exit(void);
//full_range_utils.c
void	double_ptr_free(char **dest);
int		check_valid_file_exetension(char **argv);
int		check_file_and_parsing(int argc, char **argv);
//map_valid_utils.c
int		is_square(char **map);
int		is_surround_valid_wall(char **map);
int		is_proper_element(char **map);
//map_valid_wall_utils.c
int		check_first_wall(char **map);
int		check_middle_wall(char **map);
int		check_last_wall(char **map);
//map_valid_element_utils.c
int		count_person_element(char **map);
int		count_exit_element(char **map);
int		count_collectible_element(char **map);
//game.c
t_game	*init_game_map(void);
void	set_param(t_game *game, char **input_map);
void	find_person_pos(t_game *game, char **input_map);
//draw.c
void	draw_pixel(t_game *game, char map_element, int width, int height);
void	draw_map(t_game *game);
//event.c
int		press_key_event(int key_code, t_game *game);
int		event_end_game(t_game *game);
//key_event.c
void	move_up(t_game *game, t_map_info *info);
void	move_down(t_game *game, t_map_info *info);
void	move_right(t_game *game, t_map_info *info);
void	move_left(t_game *game, t_map_info *info);
//path_struct_utils.c
t_path	*init_path(t_path *path);
void	set_path_param(t_path *path, char **input_map);
void	set_path_position(t_path *path, char **input_map);
void	release_path_struct(t_path*path);
//map_valid_path.c
int		check_path(char **map);
void	dfs(t_path *path, int y, int x);

#endif

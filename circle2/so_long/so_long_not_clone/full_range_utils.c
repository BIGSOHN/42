/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_range_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:38:25 by ssohn             #+#    #+#             */
/*   Updated: 2024/08/12 11:15:34 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	double_ptr_free(char **dest)
{
	int	i;

	i = 0;
	while (dest[i] != NULL)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

int	check_valid_file_exetension(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".ber", 4) == 0)
		return (1);
	return (0);
}

int	check_file_and_parsing(int argc, char **argv)
{
	int		fd;
	int		input_height;
	char	**temp_map;
	char	**result_map;

	if (argc != 2)
		fail_proper_argument_msg_exit();
	if (check_valid_file_exetension(argv) == 0)
		fail_valid_file_exetension_msg_exit();
	input_height = count_input_map_line(argv);
	if (input_height == 0)
		fail_file_is_empty_msg_exit();
	temp_map = make_map(argv);
	if (check_map_valid(temp_map, input_height) == 0)
		fail_map_valid_msg_exit_free();
	return (1);
}

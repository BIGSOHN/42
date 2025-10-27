/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:51:48 by ssohn             #+#    #+#             */
/*   Updated: 2025/02/27 09:16:41 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub3d_types.h"

int	validate_floor_ceiling_rgb(t_file_info	*info)
{
	if (check_rgb_code_character(info->f_color) == 1)
	{
		printf("Error\nInvalid floor character in RGB code\n");
		return (1);
	}
	if (check_rgb_code_character(info->c_color) == 1)
	{
		printf("Error\nInvalid ceiling character in RGB code\n");
		return (1);
	}
	if (validate_rgb(info->f_color) == 1)
	{
		printf("Error\nInvalid floor RGB code value\n");
		return (1);
	}
	if (validate_rgb(info->c_color) == 1)
	{
		printf("Error\nInvalid ceiling RGB code value\n");
		return (1);
	}
	return (0);
}

int	check_rgb_code_character(char *all_rgb)
{
	int	i;

	i = 0;
	while (all_rgb[i] != '\0')
	{
		if (ft_strchr("+-,0123456789\n ", all_rgb[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	validate_rgb(char *all_rgb)
{
	char	**split_rgb;
	int		i;
	int		color_code;

	i = 0;
	color_code = 0;
	split_rgb = NULL;
	if (ft_word_count(all_rgb, ',') != 3)
		return (1);
	split_rgb = ft_split(all_rgb, ',');
	while (i < 3)
	{
		color_code = ft_atoi(split_rgb[i]);
		if ((is_valid_number_string(split_rgb[i]) == 0)
			|| !(color_code >= 0 && color_code <= 255))
		{
			double_ptr_free(split_rgb);
			return (1);
		}
		i++;
	}
	double_ptr_free(split_rgb);
	return (0);
}

int	is_valid_number_string(char	*color)
{
	int		i;
	int		flag;
	char	*nptr;

	i = 0;
	flag = 0;
	nptr = ft_strtrim(color, " ");
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		flag = 1;
		i++;
	}
	if (flag != 1 || nptr[i] != '\0' || ft_strlen(nptr) > 5)
	{
		free(nptr);
		return (0);
	}
	free(nptr);
	return (1);
}

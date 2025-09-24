/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:02:11 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 18:24:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_philo_data	data;
	t_philos		*philos;
	pthread_t		monitor_thread;

	if (is_error(argc, argv) == 1)
		return (0);
	if (init_data(&data, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &data) != 0)
		return (1);
	philo_runtime(&data, philos, &monitor_thread);
	cleanup(&data);
	free(philos);
	return (0);
}

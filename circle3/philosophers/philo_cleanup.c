/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:28:22 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 21:17:58 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	cleanup(t_philo_data *data)
{
	destroy_mutex(data);
	free(data->forks);
	free(data->mutexes_meal);
}

void	destroy_mutex(t_philo_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_stop);
	while (i < data->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->mutexes_meal[i]);
		i++;
	}
}

int	error_data(t_philo_data *data, int error_code)
{
	if (error_code >= 1)
		free(data->forks);
	if (error_code >= 2)
		free(data->mutexes_meal);
	return (1);
}

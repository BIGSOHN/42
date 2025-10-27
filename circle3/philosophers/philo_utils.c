/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:28:20 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 18:24:01 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	get_time(void)
{
	struct timeval	my_time;
	long long		result;

	gettimeofday(&my_time, NULL);
	result = ((size_t)my_time.tv_sec * 1000) + ((size_t)my_time.tv_usec / 1000);
	return (result);
}

void	philo_print(t_philo_data *data, t_philos *philo, char *msg)
{
	long long	current_time;

	current_time = 0;
	pthread_mutex_lock(&data->mutex_print);
	if (check_stop_flag(data) == 0)
	{
		current_time = get_time();
		printf("%lld %d %s\n", \
				current_time - data->time_to_start, philo->p_id, msg);
	}
	pthread_mutex_unlock(&data->mutex_print);
}

void	philo_usleep(long long wait_time, t_philo_data *data)
{
	long long	start_time;
	long long	elapsed_time;

	start_time = get_time();
	elapsed_time = 0;
	while (1)
	{
		if (check_stop_flag(data) == 1)
			break ;
		elapsed_time = get_time();
		if ((elapsed_time - start_time) >= wait_time)
			break ;
		usleep(10);
	}
}

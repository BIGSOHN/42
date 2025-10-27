/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_function.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 23:05:09 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/22 19:35:53 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	philo_runtime(t_philo_data *data, t_philos *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_create(&(philos[i].thread), NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitoring, philos);
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(*monitor, NULL);
}

void	*routine(void *arg)
{
	t_philos		*philo;
	t_philo_data	*data;

	philo = (t_philos *)arg;
	data = philo->p_data;
	pthread_mutex_lock(philo->p_mutex_meal);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->p_mutex_meal);
	while (1)
	{
		if (philo->p_id % 2 == 0)
			usleep(0.5 * data->time_to_eat);
		if (pickup(data, philo) == 0)
			break ;
		if (eating(data, philo) == 0)
			break ;
		if (sleeping(data, philo) == 0)
			break ;
		if (thinking(data, philo) == 0)
			break ;
	}
	return (NULL);
}

int	sleeping(t_philo_data *data, t_philos *philo)
{
	if (check_stop_flag(data) == 1)
		return (0);
	philo_print(data, philo, "is sleeping");
	philo_usleep(data->time_to_sleep, data);
	return (1);
}

int	thinking(t_philo_data *data, t_philos *philo)
{
	if (check_stop_flag(data) == 1)
		return (0);
	philo_print(data, philo, "is thinking");
	return (1);
}

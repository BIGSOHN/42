/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 11:53:12 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 18:26:05 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitoring(void *arg)
{
	t_philos		*philos;
	t_philo_data	*data;

	philos = (t_philos *)arg;
	data = philos->p_data;
	while (1)
	{
		if (check_stop_flag(data) == 1)
			break ;
		if (check_philos_state(data, philos) == 1)
			break ;
		usleep(10);
	}
	return (NULL);
}

int	check_stop_flag(t_philo_data *data)
{
	pthread_mutex_lock(&data->mutex_stop);
	if (data->stop_flag == 1)
	{
		pthread_mutex_unlock(&data->mutex_stop);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_stop);
	return (0);
}

int	check_philos_state(t_philo_data *data, t_philos *philos)
{
	int	i;
	int	full_philos;

	i = 0;
	full_philos = 0;
	while (i < data->num_of_philo)
	{
		if (check_philo_death(data, &philos[i]) == 1)
			return (1);
		if (check_philo_full(data, &philos[i]) == 1)
			full_philos++;
		i++;
	}
	if (data->num_of_eat != -1 && full_philos == data->num_of_philo)
	{
		pthread_mutex_lock(&data->mutex_stop);
		data->stop_flag = 1;
		pthread_mutex_unlock(&data->mutex_stop);
		return (1);
	}
	return (0);
}

int	check_philo_full(t_philo_data *data, t_philos *philo)
{
	int	full_philo;

	full_philo = 0;
	if (data->num_of_eat == -1)
		return (0);
	pthread_mutex_lock(philo->p_mutex_meal);
	if (philo->p_num_of_eat >= data->num_of_eat)
		full_philo = 1;
	pthread_mutex_unlock(philo->p_mutex_meal);
	return (full_philo);
}

int	check_philo_death(t_philo_data *data, t_philos *philo)
{
	pthread_mutex_lock(philo->p_mutex_meal);
	if (get_time() - philo->last_meal_time > data->time_to_die)
	{
		pthread_mutex_unlock(philo->p_mutex_meal);
		philo_print(data, philo, "died");
		pthread_mutex_lock(&data->mutex_stop);
		data->stop_flag = 1;
		pthread_mutex_unlock(&data->mutex_stop);
		return (1);
	}
	pthread_mutex_unlock(philo->p_mutex_meal);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_behavior_eat_function.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:34:44 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 18:24:20 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	pickup(t_philo_data *data, t_philos *philo)
{
	if (check_stop_flag(data) == 1)
		return (0);
	if (data->num_of_philo == 1)
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		philo_print(data, philo, "has taken a fork");
		pthread_mutex_unlock(&data->forks[philo->left]);
		return (0);
	}
	if (philo->p_id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->right]);
		philo_print(data, philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left]);
		philo_print(data, philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->left]);
		philo_print(data, philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right]);
		philo_print(data, philo, "has taken a fork");
	}
	return (1);
}

int	eating(t_philo_data *data, t_philos *philo)
{
	if (check_stop_flag(data) == 1)
	{
		putdown(data, philo);
		return (0);
	}
	philo_print(data, philo, "is eating");
	pthread_mutex_lock(philo->p_mutex_meal);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(philo->p_mutex_meal);
	philo_usleep(data->time_to_eat, data);
	pthread_mutex_lock(philo->p_mutex_meal);
	philo->p_num_of_eat++;
	pthread_mutex_unlock(philo->p_mutex_meal);
	putdown(data, philo);
	if (check_stop_flag(data) == 1)
		return (0);
	return (1);
}

void	putdown(t_philo_data *data, t_philos *philo)
{
	if (philo->p_id % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->left]);
		pthread_mutex_unlock(&data->forks[philo->right]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->right]);
		pthread_mutex_unlock(&data->forks[philo->left]);
	}
}

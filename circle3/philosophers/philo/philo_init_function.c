/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:26:16 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 21:18:24 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_data(t_philo_data *data, int argc, char **argv)
{
	data->stop_flag = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoll(argv[2]);
	data->time_to_eat = ft_atoll(argv[3]);
	data->time_to_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		data->num_of_eat = ft_atoi(argv[5]);
	else
		data->num_of_eat = -1;
	data->time_to_start = get_time();
	return (init_mutex(data));
}

int	init_mutex(t_philo_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(data->mutex_print), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(data->mutex_stop), NULL) != 0)
		return (1);
	data->forks = (pthread_mutex_t *)malloc \
					(data->num_of_philo * sizeof(pthread_mutex_t));
	if (data->forks == NULL)
		return (error_data(data, 0));
	data->mutexes_meal = (pthread_mutex_t *)malloc \
						(data->num_of_philo * sizeof(pthread_mutex_t));
	if (data->mutexes_meal == NULL)
		return (error_data(data, 1));
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (error_data(data, 2));
		if (pthread_mutex_init(&(data->mutexes_meal[i]), NULL) != 0)
			return (error_data(data, 2));
		i++;
	}
	return (0);
}

int	init_philo(t_philos **philo, t_philo_data *data)
{
	int	i;

	i = 0;
	*philo = (t_philos *)malloc(sizeof(t_philos) * data->num_of_philo);
	if (*philo == NULL)
		return (error_data(data, 2));
	while (i < data->num_of_philo)
	{
		(*philo)[i].p_id = i + 1;
		(*philo)[i].p_num_of_eat = 0;
		(*philo)[i].left = i;
		(*philo)[i].right = (i + 1) % data->num_of_philo;
		(*philo)[i].p_data = data;
		(*philo)[i].last_meal_time = data->time_to_start;
		(*philo)[i].p_mutex_meal = &data->mutexes_meal[i];
		i++;
	}
	return (0);
}

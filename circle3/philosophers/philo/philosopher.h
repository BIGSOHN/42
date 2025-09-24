/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:58:21 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/20 21:18:50 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo_data
{
	int				stop_flag;
	int				num_of_philo;
	int				num_of_eat;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		time_to_start;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	*mutexes_meal;
	pthread_mutex_t	*forks;
}t_philo_data;

typedef struct s_philos
{
	int				p_id;
	int				p_num_of_eat;
	int				left;
	int				right;
	long long		last_meal_time;
	pthread_t		thread;
	t_philo_data	*p_data;
	pthread_mutex_t	*p_mutex_meal;
}t_philos;

//philo_behavior_eat_function.c
int			pickup(t_philo_data *data, t_philos *philo);
int			eating(t_philo_data *data, t_philos *philo);
void		putdown(t_philo_data *data, t_philos *philo);
//philo_behavior_function.c
void		philo_runtime( \
			t_philo_data *data, t_philos *philos, pthread_t *monitor);
void		*routine(void *arg);
int			sleeping(t_philo_data *data, t_philos *philo);
int			thinking(t_philo_data *data, t_philos *philo);
//philo_cleanup.c
void		cleanup(t_philo_data *data);
void		destroy_mutex(t_philo_data *data);
int			error_data(t_philo_data *data, int error_code);
//philo_monitoring.c
void		*monitoring(void *arg);
int			check_stop_flag(t_philo_data *data);
int			check_philos_state(t_philo_data *data, t_philos *philos);
int			check_philo_full(t_philo_data *data, t_philos *philo);
int			check_philo_death(t_philo_data *data, t_philos *philo);
//philo_itit_function.c
int			init_data(t_philo_data *data, int argc, char **argv);
int			init_mutex(t_philo_data *data);
int			init_philo(t_philos **philo, t_philo_data *data);
//philo_utils.c
long long	get_time(void);
void		philo_print(t_philo_data *data, t_philos *philo, char *msg);
void		philo_usleep(long long wait_time, t_philo_data *data);
//philo_libftutils.c
int			ft_isdigit(int c);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
long long	ft_atoll(const char *nptr);
int			ft_atoi(const char *nptr);
//philo_is_error.c
int			is_error(int argc, char **argv);
int			is_input_invalid(int argc, char **argv);
int			is_minus_num(int argc, char **argv);
void		ft_putstr_fd(char *s, int fd);
int			ft_check_valid_number(char *nptr);

#endif
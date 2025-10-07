/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42->fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########->fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	init_time_n_flags(t_data *data, char **argv)
{
	struct timeval	tv;

	data->no_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->no_meals_for_x_philo = ft_atoi(argv[5]);
	else
		data->no_meals_for_x_philo = -1;
	data->philo_died = 0;
	data->all_ate = 0;
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int	create_philo(t_data *data, t_philo *philos)
{
	int	n;

	(void)philos;
	n = 0;
	while (n < data->no_philo)
	{
		data->philos[n].id = n + 1;
		data->philos[n].last_meal_time = data->start_time;
		data->philos[n].left_fork = &data->fork[n];
		data->philos[n].right_fork = &data->fork[(n + 1) % data->no_philo];
		data->philos[n].data = data;
		data->philos[n].eat_count = 0;
		if (pthread_create(&data->philos[n].thread_id, NULL, philo_routine,
				&data->philos[n]) != 0)
			return (-1);
		n++;
	}
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (-1);
	return (0);
}

int	init_data_struct(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	init_time_n_flags(data, argv);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->fork)
		return (-1);
	data->philos = malloc(sizeof(t_philo) * data->no_philo);
	if (!data->philos)
		return (-1);
	return (0);
}

int	init_struct(t_data *data, char **argv)
{
	if (init_data_struct(data, argv) == -1)
		return (-1);
	if (init_mutexes(data) == -1)
		return (-1);
	return (0);
}

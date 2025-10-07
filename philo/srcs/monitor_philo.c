/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:56:47 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/20 15:56:49 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_death(t_data *data)
{
	int		i;
	long	time_since_last_meal;

	i = 0;
	while (i < data->no_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		time_since_last_meal = current_time_ms()
			- data->philos[i].last_meal_time;
		if (time_since_last_meal >= data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->philo_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			print_action(&data->philos[i], "died");
			pthread_mutex_unlock(&data->meal_mutex);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	return (0);
}

int	check_all_philos_ate(t_data *data)
{
	int	i;
	int	philo_max_meals_counts;

	if (data->no_meals_for_x_philo == -1)
		return (0);
	i = 0;
	philo_max_meals_counts = 0;
	while (i < data->no_philo)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].eat_count == data->no_meals_for_x_philo)
			philo_max_meals_counts++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (philo_max_meals_counts == data->no_philo)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

int	monitor_check_philos(t_data *data)
{
	if (check_philo_death(data))
		return (1);
	if (check_all_philos_ate(data))
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (monitor_check_philos(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

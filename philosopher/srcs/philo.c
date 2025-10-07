/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:53:48 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/20 15:53:50 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->eat_count >= philo->data->no_meals_for_x_philo
		&& philo->data->no_meals_for_x_philo != -1)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, " is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = current_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (1);
}

int	right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (philo->eat_count >= philo->data->no_meals_for_x_philo
		&& philo->data->no_meals_for_x_philo != -1)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_lock(philo->right_fork);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	print_action(philo, " is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = current_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (1);
}

int	philo_should_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->philo_died || philo->data->all_ate)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	locked;

	locked = 0;
	if (philo->id % 2 == 0)
		locked = left_fork(philo);
	else
		locked = right_fork(philo);
	if (locked)
	{
		ft_sleep(philo->data->time_to_eat, philo->data);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->data->no_philo == 1)
		{
			ft_sleep(philo->data->time_to_die, philo->data);
			break ;
		}
		if (philo_should_stop(philo))
			break ;
		philo_eat(philo);
		print_action(philo, " is sleeping");
		ft_sleep(philo->data->time_to_sleep, philo->data);
		print_action(philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}

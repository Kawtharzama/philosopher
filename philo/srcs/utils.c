/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:35:50 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/20 19:35:59 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *action)
{
	int	died;

	pthread_mutex_lock(&philo->data->death_mutex);
	died = philo->data->philo_died;
	pthread_mutex_unlock(&philo->data->death_mutex);
	if (died && ft_strncmp(action, "died", 4) != 0)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%lld %d %s\n", current_time_ms() - philo->data->start_time,
		philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_sleep(int duration_ms, t_data *data)
{
	long	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < duration_ms)
	{
		pthread_mutex_lock(&data->death_mutex);
		if (data->philo_died || data->all_ate)
		{
			pthread_mutex_unlock(&data->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->death_mutex);
		usleep(50);
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

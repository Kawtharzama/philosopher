/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42->fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########->fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	clean_philo(t_data *data)
{
	free(data->philos);
}

void	clean_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
}

void	free_structs(t_data *data)
{
	if (data)
	{
		if (data->fork)
			clean_fork(data);
		if (data->philos)
			clean_philo(data);
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->death_mutex);
		pthread_mutex_destroy(&data->meal_mutex);
		free(data);
		data = NULL;
	}
}

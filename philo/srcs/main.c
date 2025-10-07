/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42->fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########->fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	run_simulation(t_data *data, char **argv)
{
	pthread_t	monitor_thread;

	if (init_struct(data, argv) == -1)
	{
		free_structs(data);
		return (1);
	}
	if (create_philo(data, data->philos) == -1)
	{
		free_structs(data);
		return (1);
	}
	usleep(10000);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) != 0)
	{
		free_structs(data);
		return (1);
	}
	join_threads(data);
	pthread_join(monitor_thread, NULL);
	free_structs(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		i;

	i = 0;
	if (check_args(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	i = run_simulation(data, argv);
	return (i);
}

// int	main(int argc, char **argv)
// {
// 	t_data		*data;
// 	pthread_t	monitor_thread;

// 	if (check_args(argc, argv))
// 		return (1);
// 	data = malloc(sizeof(t_data));
// 	if (!data)
// 		return (1);
// 	if (init_struct(data, argv) == -1)
// 	{
// 		free_structs(data);
// 		return (1);
// 	}
// 	if (create_philo(data, data->philos) == -1)
// 	{
// 		free_structs(data);
// 		return (1);
// 	}
// 	usleep(10000);
// 	if (pthread_create(&monitor_thread, NULL, monitor_routine, data) == -1)
// 	{
// 		free_structs(data);
// 		return (1);
// 	}
// 	join_threads(data);
// 	pthread_join(monitor_thread, NULL);
// 	free_structs(data);
// 	return (0);
// }

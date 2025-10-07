/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42->fr>                    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:48:59 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/05/07 12:49:07 by kabu-zee         ###   ########->fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_all_digits(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
	{
		write(2, "./philo 1 2 3 4 5\n", 18);
		return (1);
	}
	while (i < argc)
	{
		if (!is_all_digits(argv[i]) || ft_atoi(argv[i]) <= 0)
		{
			write(2, "./philo 1 2 3 4 5\n", 18);
			return (1);
		}
		i++;
	}
	return (0);
}

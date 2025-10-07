/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabu-zee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:59:17 by kabu-zee          #+#    #+#             */
/*   Updated: 2025/06/20 15:59:19 by kabu-zee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_phlio
{
	int					id;
	long long			last_meal_time;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					eat_count;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					no_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	int					no_meals_for_x_philo;

	int					philo_died;
	int					all_ate;
	int					go_flag;

	long long			start_time;

	pthread_mutex_t		*fork;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		meal_mutex;

	t_philo				*philos;

}						t_data;

// check_args
int						check_args(int argc, char **argv);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *nptr);
int						is_all_digits(char *str);
// init
int						init_struct(t_data *data, char **argv);
int						create_philo(t_data *data, t_philo *philos);
void					init_time(t_data *data, char **argv);
// free
void					free_structs(t_data *data);

// utils
void					print_action(t_philo *philo, char *action);
long long				current_time_ms(void);
void					ft_sleep(int duration_ms, t_data *data);
void					join_threads(t_data *data);
// philo
int						right_fork(t_philo *philo);
int						left_fork(t_philo *philo);
void					*philo_routine(void *arg);

// monitor
int						check_philo_death(t_data *data);
int						check_all_philos_ate(t_data *data);
int						monitor_check_philos(t_data *data);
void					*monitor_routine(void *arg);
int						run_simulation(t_data *data, char **argv);
#endif

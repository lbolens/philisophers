/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:43:24 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 14:45:24 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_table	t_table;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					philo_id;
	long				nbr_meals;
	bool				is_it_full;
	long				last_meal;
	pthread_mutex_t		last_meal_mutex;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				nbr_philo;
	long				time_die;
	long				time_eat;
	long				time_sleep;
	long				max_meals;
	long				time_start;
	long				time_end;
	t_fork				*forks;
	t_philo				*philos;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		stop_mutex;
	bool				is_dead;
	pthread_t			check_dead;
}						t_table;

// Parsing
bool					parsing(t_table *table, long *argv);

// Init data
void					init_data(t_table *table, long *argv);

// Init dinner
void					init_dinner(t_table *table, long *args);

// Utils
void					exit_program(t_table *table, long *args, int i);
long					get_time(void);
int						ft_atol(const char *str);

// Utils routine - CORRECTED: changed return types to bool
bool					check_if_simulation_done(t_table *table);
void					print_forks_and_start_dinner(t_table *table,
							t_philo *philos);
bool					check_before_sleep(t_table *table, t_philo *philos);
bool					check_before_thinking(t_table *table, t_philo *philos);
bool					check_after_forks_if_died(t_table *table,
							t_fork *first_fork, t_fork *second_fork);

// Utils routine bis - CORRECTED: removed unused parameter
void					update_last_meal(t_table *table, t_philo *philos);
void					manage_dead(t_table *table, t_philo *philos, int i);
void					*reduce_function(t_table *table, t_philo *philos,
							int i);
void					*reduce_function_bis(int *i, int *all_full,
							t_table *table, t_philo *philos);

#endif
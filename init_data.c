/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:20:12 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 14:36:49 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_forks(t_fork *forks, t_philo *philos, t_table *table, int i,
		long *argv)
{
	if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
		exit_program(table, argv, 0);
	forks[i].fork_id = i;
	philos[i].left_fork = &forks[i];
	philos[i].right_fork = &forks[(i + 1) % table->nbr_philo];
}

static void	init_philos(t_philo *philos, t_table *table, int i)
{
	philos->philo_id = i + 1;
	philos->nbr_meals = 0;
	philos->is_it_full = false;
	philos->last_meal = table->time_start;
	philos->table = table;
	if (pthread_mutex_init(&philos->last_meal_mutex, NULL) != 0)
		exit_program(table, NULL, 0);
}

static void	init_table(t_table *table, t_fork *forks, long *argv)
{
	table->forks = forks;
	table->time_start = get_time();
	table->time_end = 0;
	table->time_eat = argv[3];
	table->time_sleep = argv[4];
	table->time_die = argv[2];
	table->is_dead = false;
}

void	init_data(t_table *table, long *argv)
{
	t_philo	*philos;
	t_fork	*forks;
	int		i;

	if (pthread_mutex_init(&table->stop_mutex, NULL) != 0)
		exit_program(table, argv, 0);
	philos = malloc(table->nbr_philo * sizeof(t_philo));
	if (!philos)
		exit_program(table, argv, 0);
	table->philos = philos;
	forks = malloc(table->nbr_philo * sizeof(t_fork));
	if (!forks)
		exit_program(table, argv, 0);
	init_table(table, forks, argv);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		exit_program(table, argv, 0);
	i = 0;
	while (i < table->nbr_philo)
	{
		init_forks(forks, philos, table, i, argv);
		init_philos(&philos[i], table, i);
		i++;
	}
}

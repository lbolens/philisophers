/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:43:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/08/21 10:41:57 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (table->max_meals == -1 || philo->nbr_meals < table->max_meals)
	{
		if (!check_if_simulation_done(table))
			return (NULL);
		if (!take_forks_and_eat(philo, table))
			return (NULL);
		if (table->max_meals != -1 && philo->nbr_meals >= table->max_meals)
			break ;
		if (!handle_sleep_and_think(table, philo))
			return (NULL);
	}
	return (NULL);
}

static void	*monitor_check_dead(void *arg)
{
	t_table	*table;
	t_philo	*philos;
	int		i;
	int		all_full;

	table = (t_table *)arg;
	philos = table->philos;
	while (!table->is_dead)
	{
		i = 0;
		if (table->max_meals != -1)
			if (!reduce_function_bis(&i, &all_full, table, philos))
				return (NULL);
		i = 0;
		while (i < table->nbr_philo)
		{
			if (!reduce_function(table, philos, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	init_dinner(t_table *table, long *args)
{
	t_philo	*philos;
	int		i;

	philos = table->philos;
	pthread_create(&table->check_dead, NULL, monitor_check_dead, table);
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_create(&philos[i].thread_id, NULL, routine,
				&philos[i]) != 0)
			exit_program(table, args, 0);
		i++;
	}
	i = 0;
	while (i < table->nbr_philo)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			exit_program(table, args, 0);
		i++;
	}
	pthread_join(table->check_dead, NULL);
}

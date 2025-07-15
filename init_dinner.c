/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:43:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 14:35:51 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo	*philos;
	t_table	*table;
	t_fork	*first_fork;
	t_fork	*second_fork;
	t_fork	*temp;

	philos = (t_philo *)arg;
	table = philos->table;
	while (table->max_meals == -1 || philos->nbr_meals < table->max_meals)
	{
		if (!check_if_simulation_done(table))
			return (NULL);
		first_fork = philos->left_fork;
		second_fork = philos->right_fork;
		if (first_fork->fork_id > second_fork->fork_id)
		{
			temp = first_fork;
			first_fork = second_fork;
			second_fork = temp;
		}
		pthread_mutex_lock(&first_fork->fork);
		pthread_mutex_lock(&second_fork->fork);
		if (!check_after_forks_if_died(table, first_fork, second_fork))
			return (NULL);
		print_forks_and_start_dinner(table, philos);
		update_last_meal(table, philos);
		pthread_mutex_unlock(&second_fork->fork);
		pthread_mutex_unlock(&first_fork->fork);
		if (table->max_meals != -1 && philos->nbr_meals >= table->max_meals)
			break ;
		if (!check_before_sleep(table, philos))
			return (NULL);
		if (!check_before_thinking(table, philos))
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

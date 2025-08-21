/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:15:03 by lbolens           #+#    #+#             */
/*   Updated: 2025/08/21 10:41:35 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_sleep_and_think(t_table *table, t_philo *philo)
{
	if (!check_before_sleep(table, philo))
		return (0);
	if (!check_before_thinking(table, philo))
		return (0);
	return (1);
}

void	update_last_meal(t_table *table, t_philo *philos)
{
	pthread_mutex_lock(&philos->last_meal_mutex);
	philos->last_meal = get_time();
	philos->nbr_meals++;
	if (table->max_meals != -1 && philos->nbr_meals >= table->max_meals)
		philos->is_it_full = true;
	pthread_mutex_unlock(&philos->last_meal_mutex);
	usleep(table->time_eat * 1000);
}

void	manage_dead(t_table *table, t_philo *philos, int i)
{
	pthread_mutex_lock(&table->print_mutex);
	printf("%ld %d died\n", get_time() - table->time_start, philos[i].philo_id);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_lock(&table->stop_mutex);
	table->is_dead = true;
	pthread_mutex_unlock(&table->stop_mutex);
}

void	*reduce_function(t_table *table, t_philo *philos, int i)
{
	long	last_meal_time;

	pthread_mutex_lock(&table->stop_mutex);
	if (table->is_dead)
	{
		pthread_mutex_unlock(&table->stop_mutex);
		return (NULL);
	}
	pthread_mutex_unlock(&table->stop_mutex);
	pthread_mutex_lock(&philos[i].last_meal_mutex);
	last_meal_time = philos[i].last_meal;
	pthread_mutex_unlock(&philos[i].last_meal_mutex);
	if (get_time() - last_meal_time > table->time_die)
	{
		manage_dead(table, philos, i);
		return (NULL);
	}
	return ((void *)1);
}

void	*reduce_function_bis(int *i, int *all_full, t_table *table,
		t_philo *philos)
{
	bool	philo_full;

	*all_full = 1;
	while (*i < table->nbr_philo)
	{
		pthread_mutex_lock(&philos[*i].last_meal_mutex);
		philo_full = philos[*i].is_it_full;
		pthread_mutex_unlock(&philos[*i].last_meal_mutex);
		if (!philo_full)
		{
			*all_full = 0;
			break ;
		}
		(*i)++;
	}
	if (*all_full)
	{
		pthread_mutex_lock(&table->stop_mutex);
		table->is_dead = true;
		pthread_mutex_unlock(&table->stop_mutex);
		return (NULL);
	}
	return ((void *)1);
}

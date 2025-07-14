/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:43:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 11:56:52 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_table *table = philos->table;
  
    while(table->max_meals == -1 || philos->nbr_meals < table->max_meals)
    {
        pthread_mutex_lock(&philos->left_fork->fork);
        pthread_mutex_lock(&philos->right_fork->fork);
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d has taken a fork\n", get_time() - table->time_start, philos->philo_id);        pthread_mutex_unlock(&table->print_mutex);
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is eating\n", get_time() - table->time_start, philos->philo_id);        pthread_mutex_unlock(&table->print_mutex);
        philos->last_meal = get_time();
        philos->nbr_meals++;
        usleep(table->time_eat * 1000);
        pthread_mutex_unlock(&philos->right_fork->fork);
        pthread_mutex_unlock(&philos->left_fork->fork);
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is sleeping\n", get_time() - table->time_start, philos->philo_id);        pthread_mutex_unlock(&table->print_mutex);
        usleep(table->time_sleep * 1000);
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is thinking\n", get_time() - table->time_start, philos->philo_id);        pthread_mutex_unlock(&table->print_mutex);
    }
    return NULL;
}

void    init_dinner(t_table *table, t_philo *philos)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]) != 0)
            exit_program(table);
        i++;    
    }
    i = 0;
    while (i < table->nbr_philo)
    {
        if (pthread_join(philos[i].thread_id, NULL) != 0)
            exit_program(table);
        i++;
    }
}
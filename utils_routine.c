/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 11:48:49 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 12:10:28 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void check_if_simulation_done(t_table *table)
{
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
            pthread_mutex_unlock(&table->stop_mutex);
        pthread_mutex_unlock(&table->stop_mutex);
}

void print_forks_and_start_dinner(t_table *table, t_philo *philos)
{
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d has taken a fork\n",
               get_time() - table->time_start, philos->philo_id);
        printf("%ld %d has taken a fork\n",
               get_time() - table->time_start, philos->philo_id);
        printf("%ld %d is eating\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);
}

void check_before_sleep(t_table *table, t_philo *philos)
{
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
        }
        pthread_mutex_unlock(&table->stop_mutex);

        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is sleeping\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);

        usleep(table->time_sleep * 1000);    
}

void check_before_thinking(t_table *table, t_philo *philos)
{
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
        }
        pthread_mutex_unlock(&table->stop_mutex);

        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is thinking\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);
}

void check_after_forks_if_died(t_table *table, t_fork *first_fork, t_fork *second_fork)
{
    pthread_mutex_lock(&table->stop_mutex);
    if (table->is_dead)
    {
        pthread_mutex_unlock(&table->stop_mutex);
        pthread_mutex_unlock(&second_fork->fork);
        pthread_mutex_unlock(&first_fork->fork);
    }
}

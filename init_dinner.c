/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:43:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 17:05:57 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    t_table *table = philos->table;

    while (table->max_meals == -1 || philos->nbr_meals < table->max_meals)
    {
        // Vérifier si simulation terminée
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&table->stop_mutex);

        // Prendre les fourchettes
        pthread_mutex_lock(&philos->left_fork->fork);
        pthread_mutex_lock(&philos->right_fork->fork);

        // Vérifier après avoir pris les forks si quelqu'un est mort
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
            pthread_mutex_unlock(&philos->right_fork->fork);
            pthread_mutex_unlock(&philos->left_fork->fork);
            return NULL;
        }
        pthread_mutex_unlock(&table->stop_mutex);

        // Affichage prise des fourchettes et début repas
        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d has taken a fork\n",
               get_time() - table->time_start, philos->philo_id);
        printf("%ld %d has taken a fork\n",
               get_time() - table->time_start, philos->philo_id);
        printf("%ld %d is eating\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);

        philos->last_meal = get_time();
        philos->nbr_meals++;
        usleep(table->time_eat * 1000);

        pthread_mutex_unlock(&philos->right_fork->fork);
        pthread_mutex_unlock(&philos->left_fork->fork);

        // Vérifier avant de dormir
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&table->stop_mutex);

        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is sleeping\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);

        usleep(table->time_sleep * 1000);

        // Vérifier avant de penser
        pthread_mutex_lock(&table->stop_mutex);
        if (table->is_dead)
        {
            pthread_mutex_unlock(&table->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&table->stop_mutex);

        pthread_mutex_lock(&table->print_mutex);
        printf("%ld %d is thinking\n",
               get_time() - table->time_start, philos->philo_id);
        pthread_mutex_unlock(&table->print_mutex);
    }
    return NULL;
}

static void *monitor_check_dead(void *arg)
{
    t_table *table = (t_table *)arg;
    t_philo *philos = table->philos;
    int i;

    while (!table->is_dead)
    {
        i = 0;
        while(i < table->nbr_philo)
        {
            pthread_mutex_lock(&table->stop_mutex);
            if (table->is_dead)
            {
                pthread_mutex_unlock(&table->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->stop_mutex);
            
            if (get_time() - philos[i].last_meal > table->time_die)
            {
                pthread_mutex_lock(&table->print_mutex);
                printf("%ld %d died\n", get_time() - table->time_start, philos[i].philo_id);
                pthread_mutex_unlock(&table->print_mutex);
                
                pthread_mutex_lock(&table->stop_mutex);
                table->is_dead = true;
                pthread_mutex_unlock(&table->stop_mutex);
                return NULL;
            }
        i++;
        }
        usleep(1000);
    }
    return NULL;
}

void    init_dinner(t_table *table, long *args)
{
    t_philo *philos = table->philos;
    int i;

    pthread_create(&table->check_dead, NULL, monitor_check_dead, table);

    i = 0;
    while (i < table->nbr_philo)
    {
        if (pthread_create(&philos[i].thread_id, NULL, routine, &philos[i]) != 0)
            exit_program(table, args);
        i++;    
    }
    i = 0;
    while (i < table->nbr_philo)
    {
        if (pthread_join(philos[i].thread_id, NULL) != 0)
            exit_program(table, args);
        i++;
    }
    pthread_join(table->check_dead, NULL);
}

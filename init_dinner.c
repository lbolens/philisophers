/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dinner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:43:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 12:17:13 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void *routine(void *arg)
{
    t_philo *philos;
    t_table *table;
    t_fork *first_fork;
    t_fork *second_fork;
    t_fork *temp;
    
    philos = (t_philo *)arg;
    table = philos->table;
    while (table->max_meals == -1 || philos->nbr_meals < table->max_meals)
    {
        check_if_simulation_done(table);
        first_fork = philos->left_fork;
        second_fork = philos->right_fork;
        if (first_fork->fork_id > second_fork->fork_id) {
            temp = first_fork;
            first_fork = second_fork;
            second_fork = temp;
        }
        pthread_mutex_lock(&first_fork->fork);
        pthread_mutex_lock(&second_fork->fork);
        check_after_forks_if_died(table, first_fork, second_fork);
        pthread_mutex_unlock(&table->stop_mutex);
        print_forks_and_start_dinner(table, philos);
        update_last_meal(table, philos);
        // Libérer les fourchettes dans l'ordre inverse
        pthread_mutex_unlock(&second_fork->fork);
        pthread_mutex_unlock(&first_fork->fork);
        if (table->max_meals != -1 && philos->nbr_meals >= table->max_meals)
            break;
        check_before_sleep(table, philos);
        check_before_thinking(table, philos);
    }
    return NULL;
}

static void *monitor_check_dead(void *arg)
{
    t_table *table = (t_table *)arg;
    t_philo *philos = table->philos;
    int i;
    long last_meal_time;

    while (!table->is_dead)
    {
        i = 0;
        if (table->max_meals != -1)
        {
            int all_full = 1;
            while (i < table->nbr_philo)
            {
                if (!philos[i].is_it_full)
                {
                    all_full = 0;
                    break;
                }
                i++;
            }
            if (all_full)
            {
                pthread_mutex_lock(&table->stop_mutex);
                table->is_dead = true;
                pthread_mutex_unlock(&table->stop_mutex);
                return NULL;
            }
        }

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
            
            // Lire last_meal de façon thread-safe
            pthread_mutex_lock(&philos[i].last_meal_mutex);
            last_meal_time = philos[i].last_meal;
            pthread_mutex_unlock(&philos[i].last_meal_mutex);
            
            // Utiliser la variable locale protégée
            if (get_time() - last_meal_time > table->time_die)
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
    t_philo *philos;
    int i;

    philos = table->philos;
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

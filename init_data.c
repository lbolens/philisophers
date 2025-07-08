/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:20:12 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/08 14:22:13 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_forks(t_fork *forks, t_philo *philos, t_table *table, int i)
{
    pthread_mutex_init(&forks[i].fork,NULL);
    forks[i].fork_id = i;
    philos[i].left_fork = &forks[i];
    philos[i].right_fork = &forks[(i + 1) % table->nbr_philo];
}

void init_philos(t_philo *philos, t_table *table, int i)
{
    philos->philo_id = i;
    philos->nbr_meals = 0;
    philos->is_it_full = false;
    philos->last_meal = table->time_start;
    philos->table = table;
}

void init_data(t_table *table)
{
    t_philo *philos;
    t_fork *forks;
    int i;
    
    philos = malloc(table->nbr_philo * sizeof(t_philo));
    if (!philos)
        exit(1);
    table->philos = philos;
    forks = malloc(table->nbr_philo * sizeof(t_fork));
    if (!forks)
        exit(1);
    table->forks = forks;
    table->time_start = time;
    i = 0;
    while (i < table->nbr_philo)
    {
        init_forks(forks, philos, table, i);
        init_philos(&philos[i], table, i);
        i++;
    }
    
}

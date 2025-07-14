/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 13:20:12 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 11:59:19 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_forks(t_fork *forks, t_philo *philos, t_table *table, int i)
{
    if (pthread_mutex_init(&forks[i].fork, NULL) != 0)
        exit_program(table, philos, forks);
    forks[i].fork_id = i;
    philos[i].left_fork = &forks[i];
    philos[i].right_fork = &forks[(i + 1) % table->nbr_philo];
}

static void init_philos(t_philo *philos, t_table *table, int i)
{
    philos->philo_id = i;
    philos->nbr_meals = 0;
    philos->is_it_full = false;
    philos->last_meal = table->time_start;
    philos->table = table;
}

void init_data(t_table *table, char **argv)
{
    t_philo *philos;
    t_fork *forks;
    int i;
    
    philos = malloc(table->nbr_philo * sizeof(t_philo));
    if (!philos)
        exit_program(table, philos, forks);
    table->philos = philos;
    forks = malloc(table->nbr_philo * sizeof(t_fork));
    if (!forks)
        exit_program(table, philos, forks);
    table->forks = forks;
    table->time_start = get_time();
    table->time_end = 0;
    table->time_eat = argv[3];
    table->time_sleep = argv[4];
    table->time_die = argv[2];
    if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
        exit_program(table, philos, forks);
    i = 0;
    while (i < table->nbr_philo)
    {
        init_forks(forks, philos, table, i);
        init_philos(&philos[i], table, i);
        i++;
    }
}
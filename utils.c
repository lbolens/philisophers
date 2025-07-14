/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 10:03:02 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 10:36:25 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void)
{
    long time;
    
    gettimeofday(&time, NULL);
    return time;
}

void exit_program(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nbr_philo)
    {
        pthread_mutex_destroy(&table->forks[i].fork);
        i++;
    }
    pthread_mutex_destroy(&table->print_mutex);
    if (table->philos)
        free(table->philos);
    if (table->forks)
        free(table->forks); 
    exit(1);
}

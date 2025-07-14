/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:50:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 17:02:28 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool is_args_valid(t_table *table, long *argv)
{
    if ((argv[5] && table->max_meals <= 0) || table->nbr_philo <= 0
        || table->time_die <= 0 || table->time_eat <= 0 
        || table->time_sleep <= 0)
        return false;
    return true;
}

bool parsing(t_table *table, long *argv)
{
    table->nbr_philo = (argv[1]);
    table->time_die = (argv[2]);
    table->time_eat = (argv[3]);
    table->time_sleep = (argv[4]);
    table->max_meals = -1;
    if (argv[5])
        table->max_meals = (argv[5]);
    return(is_args_valid(table, argv));
}
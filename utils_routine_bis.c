/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:15:03 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 12:16:13 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void update_last_meal(t_table *table, t_philo *philos)
{
        pthread_mutex_lock(&philos->last_meal_mutex);
        philos->last_meal = get_time();
        pthread_mutex_unlock(&philos->last_meal_mutex);
        philos->nbr_meals++;
        if (table->max_meals != -1 && philos->nbr_meals >= table->max_meals)
            philos->is_it_full = true;
        usleep(table->time_eat * 1000);
}
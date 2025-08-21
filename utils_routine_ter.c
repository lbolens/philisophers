/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_routine_ter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:30:29 by lbolens           #+#    #+#             */
/*   Updated: 2025/08/21 10:41:39 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork_order(t_philo *philo, t_fork **first, t_fork **second)
{
	t_fork	*temp;

	*first = philo->left_fork;
	*second = philo->right_fork;
	if ((*first)->fork_id > (*second)->fork_id)
	{
		temp = *first;
		*first = *second;
		*second = temp;
	}
}

int	take_forks_and_eat(t_philo *philo, t_table *table)
{
	t_fork	*first_fork;
	t_fork	*second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	pthread_mutex_lock(&first_fork->fork);
	pthread_mutex_lock(&second_fork->fork);
	if (!check_after_forks_if_died(table, first_fork, second_fork))
		return (0);
	print_forks_and_start_dinner(table, philo);
	update_last_meal(table, philo);
	pthread_mutex_unlock(&second_fork->fork);
	pthread_mutex_unlock(&first_fork->fork);
	return (1);
}

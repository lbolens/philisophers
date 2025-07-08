/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:50:01 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/08 13:06:34 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static bool is_args_valid(t_table *table, char **argv)
{
    if ((argv[5] && table->max_meals <= 0) || table->nbr_philo <= 0
        || table->time_die <= 0 || table->time_eat <= 0 
        || table->time_sleep <= 0)
        return false;
    return true;
}

bool parsing(t_table *table, char **argv)
{
    table->nbr_philo = ft_atoi(argv[1]);
    table->time_die = ft_atoi(argv[2]);
    table->time_eat = ft_atoi(argv[3]);
    table->time_sleep = ft_atoi(argv[4]);
    table->max_meals = -1;
    if (argv[5])
        table->max_meals = ft_atoi(argv[5]);
    return(is_args_valid);
}
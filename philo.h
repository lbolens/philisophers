/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:43:24 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 17:10:37 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

struct s_table;

typedef struct s_table t_table;

typedef pthread_mutex_t mtx;

typedef struct s_fork
{
    mtx fork;
    int fork_id;
} t_fork;

typedef struct s_philo
{
    int philo_id;
    long nbr_meals;
    bool is_it_full;
    long last_meal;
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
    t_table *table;
} t_philo;

typedef struct s_table
{
    long nbr_philo;
    long time_die;
    long time_eat;
    long time_sleep;
    long max_meals;
    long time_start;
    long time_end;
    t_fork *forks;
    t_philo *philos;
    pthread_mutex_t print_mutex;
    pthread_mutex_t stop_mutex;
    bool is_dead;
    pthread_t check_dead;
} t_table;

//Parsing
bool parsing(t_table *table, long *argv);

//Init data
void init_data(t_table *table, long *argv);

//Init dinner
void    init_dinner(t_table *table, long *args);

//Utils
void exit_program(t_table *table, long *args);
long    get_time(void);
int	ft_atol(const char *str);

#endif
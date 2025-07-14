/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:43:21 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/14 17:15:09 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    int i;
    t_table table;
    long *args;
    
    if (argc != 5 || argc != 6)
    {
        long *args = malloc(argc * sizeof(long));
        if (!args)
            exit(1);
        i = 1;
        while (argv[i])
        {
            args[i] = ft_atol(argv[i]);
            i++;
        }
        
        //1) Parsing
        if (!parsing(&table, args))
        {
            printf("Error: please put correct inputs\n");
            exit(1);
        }
        //2) Init the data
        init_data(&table, args);
        //3) starting the dinner
        init_dinner(&table, args);
        //4) Exiting without leaks
        exit_program(&table, args);
    }
    else
    {
        printf("Error: please put correct inputs\n");
        exit(1);
    }
    return (0);
}

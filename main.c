/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:43:21 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/08 13:30:57 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
    t_table table;
    
    if (argc != 5 || argc != 6)
    {
        //1) Parsing
        if (!parsing(&table, argv))
        {
            printf("Error: please put correct inputs\n");
            exit(1);
        }
        //2) Init the data
        init_data(&table, argv);
        //3) starting the dinner

        //4) Exiting without leaks
        exit_program();
    }
    else
    {
        printf("Error: please put correct inputs\n");
        exit(1);
    }
    return (0);
}

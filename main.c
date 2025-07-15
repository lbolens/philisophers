/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbolens <lbolens@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:43:21 by lbolens           #+#    #+#             */
/*   Updated: 2025/07/15 14:36:03 by lbolens          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	doing_it(int argc, long *args)
{
	t_table	table;

	if (argc == 5)
		args[5] = 0;
	if (!parsing(&table, args))
	{
		printf("Error: please put correct inputs\n");
		free(args);
		exit(1);
	}
	init_data(&table, args);
	init_dinner(&table, args);
	exit_program(&table, args, 0);
}

int	main(int argc, char **argv)
{
	int		i;
	long	*args;

	if (argc != 5 && argc != 6)
	{
		printf("Error : please put correct inputs\n");
		exit(1);
	}
	args = malloc((argc + 1) * sizeof(long));
	if (!args)
		exit(1);
	i = 1;
	while (i < argc)
	{
		args[i] = ft_atol(argv[i]);
		i++;
	}
	doing_it(argc, args);
	return (0);
}

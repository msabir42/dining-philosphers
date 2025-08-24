/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:09 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:10 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check(int argc, char **argv)
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		put_string("ERROR: The number of arguments must be 5 or 6\n", 2);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			error_in_arg(i);
			return (0);
		}
		if (!check_max_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_simulation	simulation;
	int				i;

	if (!check(argc, argv))
		return (1);
	init_philo(&simulation, argc, argv);
	if (simulation.time_sleep > simulation.time_die)
		simulation.time_sleep = simulation.time_die;
	if (simulation.time_eat > simulation.time_die)
		simulation.time_eat = simulation.time_die;
	init_mutexes(&simulation);
	create_philosophers(&simulation);
	i = 0;
	while (i < simulation.number_of_philosophers)
	{
		pthread_join(simulation.philosopher[i].philosopher, NULL);
		i++;
	}
	free(simulation.fork);
	free(simulation.philosopher);
	return (0);
}

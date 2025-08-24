/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:12 by msabir            #+#    #+#             */
/*   Updated: 2025/08/24 02:20:13 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_simulation_values(t_simulation *simulation, int argc, char **argv)
{
	simulation->number_of_philosophers = ft_atoil(argv[1]);
	simulation->time_die = ft_atoil(argv[2]);
	simulation->time_eat = ft_atoil(argv[3]);
	simulation->time_sleep = ft_atoil(argv[4]);
	simulation->arg_6 = 0;
	simulation->count_meal = 0;
	simulation->stop = 0;
	simulation->start_time = get_current_time();
	if (argc == 6)
	{
		simulation->arg_6 = 1;
		simulation->must_eat = ft_atoil(argv[5]);
	}
}

void	init_philosophers_array(t_simulation *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		simulation->philosopher[i].id = i + 1;
		simulation->philosopher[i].meals_eaten = 0;
		simulation->philosopher[i].last_eat_time = get_current_time();
		simulation->philosopher[i].simulation = simulation;
		i++;
	}
}

void	init_philo(t_simulation *simulation, int argc, char **argv)
{
	init_simulation_values(simulation, argc, argv);
	simulation->philosopher = malloc(sizeof(t_philosophers)
			* simulation->number_of_philosophers);
	simulation->fork = malloc(sizeof(pthread_mutex_t)
			* simulation->number_of_philosophers);
	init_philosophers_array(simulation);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:43 by msabir            #+#    #+#             */
/*   Updated: 2025/08/24 03:24:10 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_stop(t_simulation *simulation)
{
	int	stop;

	pthread_mutex_lock(&simulation->mutex_stop);
	stop = simulation->stop;
	pthread_mutex_unlock(&simulation->mutex_stop);
	return (stop);
}

void	handle_eating(t_philosophers *philosopher, t_simulation *simulation)
{
	pthread_mutex_lock(&simulation->mutex_last_eat);
	philosopher->last_eat_time = get_current_time();
	pthread_mutex_unlock(&simulation->mutex_last_eat);
	if (!check_stop(simulation))
		print_status(philosopher, simulation, "is eating");
	pthread_mutex_lock(&simulation->mutex_count_meal);
	if (simulation->arg_6)
	{
		philosopher->meals_eaten++;
		simulation->count_meal++;
	}
	pthread_mutex_unlock(&simulation->mutex_count_meal);
	ft_usleep(simulation->time_eat);
}

int	cycle(t_philosophers *philosopher, t_simulation *simulation)
{
	if (philosopher->id % 2 == 0)
		odd_case(simulation, philosopher);
	else
	{
		usleep(500);
		even_case(simulation, philosopher);
	}
	handle_eating(philosopher, simulation);
	release_forks(philosopher, simulation);
	if (!check_stop(simulation))
		print_status(philosopher, simulation, "is sleeping");
	ft_usleep(simulation->time_sleep);
	if (!check_stop(simulation))
		print_status(philosopher, simulation, "is thinking");
	return (1);
}

int	odd_case(t_simulation *simulation, t_philosophers *philo)
{
	if (!take_first_fork_odd(simulation, philo))
		return (0);
	if (!take_second_fork_odd(simulation, philo))
		return (0);
	return (1);
}

int	even_case(t_simulation *simulation, t_philosophers *philo)
{
	if (!take_first_fork_even(simulation, philo))
		return (0);
	if (!take_second_fork_even(simulation, philo))
		return (0);
	return (1);
}

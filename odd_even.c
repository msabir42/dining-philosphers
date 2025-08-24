/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_even.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:22 by msabir            #+#    #+#             */
/*   Updated: 2025/08/24 03:24:46 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_fork_taken(t_simulation *simulation, t_philosophers *philo)
{
	printf("%ld %d %s", get_current_time() - simulation->start_time,
		philo->id, "has taken a fork\n");
}

int	take_first_fork_odd(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[philo->id
			% simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		print_fork_taken(simulation, philo);
	else
	{
		unlock_lock(simulation, philo);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

int	take_second_fork_odd(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[(philo->id - 1)
			% simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		print_fork_taken(simulation, philo);
	else
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

int	take_first_fork_even(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[(philo->id - 1)
			% simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		print_fork_taken(simulation, philo);
	else
	{
		unlock_lock(simulation, philo);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

int	take_second_fork_even(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[philo->id
			% simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		print_fork_taken(simulation, philo);
	else
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

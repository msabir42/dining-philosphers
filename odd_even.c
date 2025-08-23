/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   odd_even.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:22 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:23 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int odd_case(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[philo->id % simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
	{
		printf("%ld %d %s", get_current_time() - simulation->start_time, philo->id,
			"has taken a fork\n");
	}
	else
	{
		unlock_lock(simulation, philo);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	pthread_mutex_lock(&(simulation->fork[(philo->id - 1) % simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		printf("%ld %d %s", get_current_time() - simulation->start_time, philo->id,
			"has taken a fork\n");
	else
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

int	even_case(t_simulation *simulation, t_philosophers *philo)
{
	pthread_mutex_lock(&(simulation->fork[(philo->id - 1) % simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		printf("%ld %d %s", get_current_time() - simulation->start_time, philo->id,
			"has taken a fork\n");
	else
	{
		unlock_lock(simulation, philo);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	pthread_mutex_lock(&(simulation->fork[philo->id % simulation->number_of_philosophers]));
	pthread_mutex_lock(&simulation->mutex_printf);
	if (!simulation->stop)
		printf("%ld %d %s", get_current_time() - simulation->start_time, philo->id,
			"has taken a fork\n");
	else
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		return (0);
	}
	pthread_mutex_unlock(&simulation->mutex_printf);
	return (1);
}

void	unlock_lock(t_simulation *simulation, t_philosophers *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		pthread_mutex_lock(&(simulation->fork[(philo->id - 1) % simulation->number_of_philosophers]));
	}
	else
	{
		pthread_mutex_unlock(&simulation->mutex_printf);
		pthread_mutex_lock(&(simulation->fork[philo->id % simulation->number_of_philosophers]));
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:43 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:44 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_stop(t_simulation *simulation)
{
    int stop;

    pthread_mutex_lock(&simulation->mutex_stop);
    stop = simulation->stop;
    pthread_mutex_unlock(&simulation->mutex_stop);

    return (stop);  
}

int cycle(t_philosophers *philosopher, t_simulation *simulation)
{
    if(philosopher->id % 2 == 0)
        odd_case(simulation, philosopher);
    else
    {
            usleep(500);
            even_case(simulation, philosopher);
    }
    pthread_mutex_lock(&simulation->mutex_last_eat);
    philosopher->last_eat_time = get_current_time();
    pthread_mutex_unlock(&simulation->mutex_last_eat);
    if(!check_stop(simulation))
        print_status(philosopher, simulation, "is eating");
    pthread_mutex_lock(&simulation->mutex_count_meal);
    if(simulation->arg_6)
        philosopher->meals_eaten++;
    pthread_mutex_unlock(&simulation->mutex_count_meal);
    ft_usleep(simulation->time_eat);
    realease_forks(philosopher, simulation);
    if(!check_stop(simulation))
        print_status(philosopher, simulation, "is sleeping");
    ft_usleep(simulation->time_sleep);
    if(!check_stop(simulation))
        print_status(philosopher, simulation, "is thinking");
    return (1); 
}

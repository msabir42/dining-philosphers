/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:19 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:20 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_mutexes(t_simulation *simulation)
{
    int i;
    pthread_mutex_init(&simulation->mutex_printf, NULL);
    pthread_mutex_init(&simulation->mutex_count_meal, NULL);
    pthread_mutex_init(&simulation->mutex_last_eat, NULL);
    pthread_mutex_init(&simulation->mutex_stop, NULL);
    pthread_mutex_init(&simulation->mutex_start, NULL);
    i = 0;
    while (i < simulation->number_of_philosophers)
    {
        pthread_mutex_init(&simulation->fork[i], NULL);
        i++;
    }
}

void print_status(t_philosophers *philo, t_simulation *simulation, char *status)
{
    pthread_mutex_lock(&simulation->mutex_printf);
    if(!check_stop(simulation))
        printf("%ld %d %s\n", get_current_time() - simulation->start_time, philo->id, status);
    pthread_mutex_unlock(&simulation->mutex_printf);
}
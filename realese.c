/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realese.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:34 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:35 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void realease_forks(t_philosophers *philosopher, t_simulation *simulation)
{
    pthread_mutex_unlock(&simulation->fork[philosopher->id % simulation->number_of_philosophers]);
    pthread_mutex_unlock(&simulation->fork[(philosopher->id - 1) % simulation->number_of_philosophers]);
}
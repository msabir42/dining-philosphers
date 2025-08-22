#include "philosophers.h"

int is_died(t_philosophers *philosopher, t_simulation *simulation)
{
    pthread_mutex_lock(&simulation->mutex_last_eat);
    if ( get_current_time() - philosopher->last_eat_time > simulation->time_die)
    {
        pthread_mutex_unlock(&simulation->mutex_last_eat);

        pthread_mutex_lock(&simulation->mutex_stop);
        if (!simulation->stop) 
        {
            simulation->stop = 1;
            pthread_mutex_unlock(&simulation->mutex_stop);

            pthread_mutex_lock(&simulation->mutex_printf);
            printf("%ld %d died\n",  get_current_time()  - simulation->start_time,
                   philosopher->id + 1);
            pthread_mutex_unlock(&simulation->mutex_printf);
        }
        else
            pthread_mutex_unlock(&simulation->mutex_stop);

        return (1);
    }
    pthread_mutex_unlock(&simulation->mutex_last_eat);
    return (0);
}

int philosopher_saturation(t_philosophers *philosopher,
                           t_simulation *simulation)
{
   	pthread_mutex_lock(&simulation->mutex_count_meal);
	if (simulation->arg_6)
	{
		if (simulation->count_meal >= simulation->must_eat * simulation->number_of_philosophers)
		{
			pthread_mutex_lock(&simulation->mutex_printf);
			pthread_mutex_lock(&simulation->mutex_stop);
			simulation->stop = 1;
			pthread_mutex_unlock(&simulation->mutex_stop);
			ft_usleep(simulation->time_eat);
			pthread_mutex_unlock(&simulation->mutex_printf);
			pthread_mutex_unlock(&simulation->mutex_count_meal);
			return (0);
		}
	}
	pthread_mutex_unlock(&simulation->mutex_count_meal);
	return (1);
}

int is_end_simulation(t_simulation *simulation)
{
   int	i;

	i = 0;
	while (i < simulation->number_of_philosophers)
	{
		if (!check_death(simulation, i))
		{
			return (0);
		}
		if (!check_full(simulation))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

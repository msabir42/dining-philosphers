#include "philosophers.h"

void routine(void* arg)
{
    t_philosophers *philo;
    t_simulation *simulation;

    philo - (t_philosophers *)arg;
    simulation = philo->simulation;

    pthread_mutex_lock(&simulation->mutex_start);
    pthread_mutex_unlock(&simulation->mutex_start);

    while (simulation->number_of_philosophers == 1)
    {
        pthread_mutex_lock(&simulation->fork[(philo ->id - 1) % simulation->number_of_philosophers]);
        printf("%ld %d %s", get_current_time() - simulation->start_time, philo->id, "has taken a fork\n");
        return(NULL);
    }
    while(RUN)
    {
		if (check_stop(simulation))
			return (NULL);
		if (printf_status(simulation, philo) != 1)
			return (NULL);
	}
	return (NULL);

}

int create_philosophers(t_simulation *simulation)
{
    int i;

    i = 0;
    pthread_mutex_lock(&simulation->mutex_start);
    while (i < simulation->number_of_philosophers)
    {
        pthread_create(&simulation->philosopher[i].philosopher, NULL, routine, &simulation->philosopher[i]);
        i++;
    }
    while (i < simulation->number_of_philosophers)
    {
        simulation->philosopher[i].last_eat_time = get_current_time();
        i++;
    }
    pthread_mutex_unlock(&simulation->mutex_start);
    while (is_end_simulation(simulation))
	{
		usleep(100);
	}
	return (0);

}


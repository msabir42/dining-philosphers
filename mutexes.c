#include "philosophers.h"

void print_status(t_philosophers *philo, t_simulation *simulation, char *status)
{
    pthread_mutex_lock(&simulation->mutex_printf);
    if(!check_stop(simulation))
        printf("%ld %d %s\n", get_current_time() - simulation->start_time, philo->id, status);
    pthread_mutex_unlock(&simulation->mutex_printf);
}
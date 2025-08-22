#include "philosophers.h"

void realease_forks(t_philosophers *philosopher, t_simulation *simulation)
{
    pthread_mutex_unlock(&simulation->fork[philosopher->id % simulation->number_of_philosophers]);
    pthread_mutex_unlock(&simulation->fork[(philosopher->id - 1) % simulation->number_of_philosophers]);
}
#include "philosophers.h"


void init_philo( t_simulation *simulation,  int argc, char **argv)
{
    int i;
    simulation->number_of_philosophers = ft_atoil(argv[1]);
    simulation->time_die = ft_atoil(argv[2]);
    simulation->time_eat = ft_atoil(argv[3]);
    simulation->time_sleep = ft_atoil(argv[4]);
    simulation->arg_6 = 0;
    simulation->count_meal = 0;
    simulation->stop = 0;
    simulation->start_time = get_current_time();
    if (argc == 6)
    {
        simulation->arg_6 = 1;
        simulation->must_eat = ft_atoil(argv[5]);
    }
    i  = 0;
    simulation->philosopher = malloc(sizeof(t_philosophers) * simulation->number_of_philosophers);
    simulation->fork = malloc(sizeof(pthread_mutex_t) * simulation->number_of_philosophers);
    while (i < simulation->number_of_philosophers)
    {
        simulation->philosopher[i].id = i + 1;
        simulation->philosopher[i].meals_eaten = 0;
        simulation->philosopher[i].last_eat_time = get_current_time();
        simulation->philosopher[i].simulation = simulation;
        i++;
    }
}
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

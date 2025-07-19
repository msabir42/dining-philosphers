#include "philo.h"


void init_philosophers(t_philosopher *philosophers,pthread_mutex_t *forks ,int n, void *arg)
{
    int i;
    i = 0;
    while (i < n)
    {
        philosophers[i].id = i;
        philosophers[i].right_fork = &forks[i];
        philosophers[i].left_fork = &forks[(i + 1) % n];
        pthread_create(&philosophers[i].thread,NULL,arg,&philosophers[i]);
        i++;
    }
}
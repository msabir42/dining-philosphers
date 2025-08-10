#include "philo.h"


void init_philosophers(t_philosopher *philosophers, t_rules *rules, int n, void *routine)
{
    int i = 0;
    while (i < n)
    {
        philosophers[i].id = i;
        philosophers[i].rules = rules;
        pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
        i++;
    }
}


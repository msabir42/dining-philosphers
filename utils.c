#include "philo.h"


void init_philosophers(t_philosopher *philosophers, t_rules *rules, int n, void *routine)
{
    int i = 0;
    while (i < n)
    {
        philosophers[i].id = i;
        philosophers[i].rules = rules;
        philosophers[i].last_meal_eaten_time = get_time(rules->start_timer);
        philosophers[i].meals_eaten = 0;
        philosophers[i].is_dead = 0;
        pthread_create(&philosophers[i].thread, NULL, routine, &philosophers[i]);
        i++;
    }
}


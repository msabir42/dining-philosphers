#include "philo.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long start_timer;

pthread_mutex_t waiter;



void* routine(void* arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_rules *rules = philo->rules;
    int left = philo->id;
    int right = (philo->id + 1) % rules->number_of_philosophers;

    while (1)
    {
        pthread_mutex_lock(&rules->waiter);
        if (rules->forks_available[left] && rules->forks_available[right])
        {
            rules->forks_available[left] = 0;
            rules->forks_available[right] = 0;
            pthread_mutex_unlock(&rules->waiter);

            printf("%d %d is eating\n", get_time(rules->start_timer), philo->id);
            usleep(rules->time_to_eat * 1000);

            pthread_mutex_lock(&rules->waiter);
            rules->forks_available[left] = 1;
            rules->forks_available[right] = 1;
            pthread_mutex_unlock(&rules->waiter);

            printf("%d %d is sleeping\n", get_time(rules->start_timer), philo->id);
            usleep(rules->time_to_sleep * 1000);

            printf("%d %d is thinking\n", get_time(rules->start_timer), philo->id);
        }
        else
        {
            pthread_mutex_unlock(&rules->waiter);
            usleep(1000);
        }
    }
    return NULL;
}

void init_philosophers(t_philosopher *philosophers, t_rules *rules, int n, void *routine);



int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6) {
        fprintf(stderr, "Usage: %s n_philo t_die t_eat t_sleep [n_eat]\n", argv[0]);
        return 1;
    }

    t_rules rules;
    rules.number_of_philosophers = atoi(argv[1]);
    rules.time_to_die = atoi(argv[2]);
    rules.time_to_eat = atoi(argv[3]);
    rules.time_to_sleep = atoi(argv[4]);
    rules.number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;
    rules.forks_available = malloc(sizeof(int) * rules.number_of_philosophers);
    for (int i = 0; i < rules.number_of_philosophers; i++)
        rules.forks_available[i] = 1;
    pthread_mutex_init(&rules.waiter, NULL);
    time_init(&rules.start_timer);

    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * rules.number_of_philosophers);
    if (!philosophers)
        return 1;

    init_philosophers(philosophers, &rules, rules.number_of_philosophers, routine);

    for (int i = 0; i < rules.number_of_philosophers; i++)
        pthread_join(philosophers[i].thread, NULL);

    pthread_mutex_destroy(&rules.waiter);
    free(rules.forks_available);
    free(philosophers);
    return 0;
}

#include "philo.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_rules *rules = philo->rules;
    int left = philo->id;
    int right = (philo->id + 1) % rules->number_of_philosophers;

    while (!philo->is_dead)  // Add death check
    {
        pthread_mutex_lock(&rules->waiter);
        if (rules->forks_available[left] && rules->forks_available[right])
        {
            rules->forks_available[left] = 0;
            rules->forks_available[right] = 0;
            pthread_mutex_unlock(&rules->waiter);

            philo->last_meal_eaten_time = get_time(rules->start_timer);
            philo->meals_eaten++;
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

void* monitor(void* arg)
{
    t_philosopher *philosophers = (t_philosopher *)arg;
    t_rules *rules = philosophers[0].rules;
    int all_ate_enough = 0;

    while (!all_ate_enough)
    {
        for (int i = 0; i < rules->number_of_philosophers; i++)
        {
            pthread_mutex_lock(&rules->waiter);
            long time_since_meal = get_time(rules->start_timer) - philosophers[i].last_meal_time;
            
            if (time_since_meal > rules->time_to_die)
            {
                printf("%d %d died\n", get_time(rules->start_timer), i);
                philosophers[i].is_dead = 1;
                pthread_mutex_unlock(&rules->waiter);
                return NULL;
            }
            
            if (rules->number_of_times_each_philosopher_must_eat != -1)
            {
                all_ate_enough = 1;
                for (int j = 0; j < rules->number_of_philosophers; j++)
                {
                    if (philosophers[j].meals_eaten < rules->number_of_times_each_philosopher_must_eat)
                    {
                        all_ate_enough = 0;
                        break;
                    }
                }
            }
            pthread_mutex_unlock(&rules->waiter);
        }
        usleep(1000);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    if (argc != 5 && argc != 6)
    {
        fprintf(stderr, "Usage: %s n_philo t_die t_eat t_sleep [n_eat]\n", argv[0]);
        return 1;
    }

    t_rules rules;
    rules.number_of_philosophers = atoi(argv[1]);
    rules.time_to_die = atoi(argv[2]);
    rules.time_to_eat = atoi(argv[3]);
    rules.time_to_sleep = atoi(argv[4]);
    rules.number_of_times_each_philosopher_must_eat = (argc == 6) ? atoi(argv[5]) : -1;

    // Initialize forks
    rules.forks_available = malloc(sizeof(int) * rules.number_of_philosophers);
    if (!rules.forks_available)
        return 1;

    for (int i = 0; i < rules.number_of_philosophers; i++)
        rules.forks_available[i] = 1;

    pthread_mutex_init(&rules.waiter, NULL);
    time_init(&rules.start_timer);

    // Initialize philosophers
    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * rules.number_of_philosophers);
    if (!philosophers)
    {
        free(rules.forks_available);
        return 1;
    }

    // Create threads
    init_philosophers(philosophers, &rules, rules.number_of_philosophers, routine);
    pthread_t monitor_thread;
    pthread_create(&monitor_thread, NULL, monitor, philosophers);

    // Wait for threads
    for (int i = 0; i < rules.number_of_philosophers; i++)
        pthread_join(philosophers[i].thread, NULL);
    pthread_join(monitor_thread, NULL);

    // Cleanup
    pthread_mutex_destroy(&rules.waiter);
    free(rules.forks_available);
    free(philosophers);
    
    return 0;
}

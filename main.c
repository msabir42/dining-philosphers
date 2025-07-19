#include "philo.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

long start_timer;

pthread_mutex_t lock;
pthread_mutex_t print_lock;


void time_init()
{
    struct timeval t_val;
    gettimeofday(&t_val, NULL);
    start_timer = t_val.tv_sec * 1000L + t_val.tv_usec / 1000L;
}

int get_time()
{
    struct timeval t_val;
    gettimeofday(&t_val, NULL);
    long time = t_val.tv_sec * 1000L + t_val.tv_usec / 1000L - start_timer;
    return (int)time;
}


void* routine(void* arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    if (philo->id % 2 == 0)
        usleep(1000);

    while (1)
    {
        pthread_mutex_t *first = philo->left_fork;
        pthread_mutex_t *second = philo->right_fork;

        if (first > second)
        {
            pthread_mutex_t *tmp = first;
            first = second;
            second = tmp;
        }

        pthread_mutex_lock(first);
        pthread_mutex_lock(second);

        
        pthread_mutex_lock(&print_lock);
        printf("%d %d is eating\n", get_time(), philo->id);
        pthread_mutex_unlock(&print_lock);

        usleep(200 * 1000); 

        pthread_mutex_unlock(second);
        pthread_mutex_unlock(first);

        pthread_mutex_lock(&print_lock);
        printf("%d %d is sleeping\n", get_time(), philo->id);
        pthread_mutex_unlock(&print_lock);

        usleep(200 * 1000); 

        pthread_mutex_lock(&print_lock);
        printf("%d %d is thinking\n", get_time(), philo->id);
        pthread_mutex_unlock(&print_lock);
    }

    return NULL;
}

void *activities(void *arg)
{
    pthread_mutex_lock(&lock);
    int id = *(int *)arg;
    free(arg);
    usleep(2000);

    printf("%d ms philosopher %d has taken a fork\n", get_time(), id);
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    time_init();

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s number_of_philosophers\n", argv[0]);
        return 1;
    }

    int number_of_philosophers = atoi(argv[1]);
    if (number_of_philosophers <= 0)
    {
        fprintf(stderr, "Philosopher count must be positive\n");
        return 1;
    }

    pthread_mutex_t *forks = malloc(sizeof(pthread_mutex_t) * number_of_philosophers);
    t_philosopher *philosophers = malloc(sizeof(t_philosopher) * number_of_philosophers);
    if (!forks || !philosophers)
        return 1;

    for (int i = 0; i < number_of_philosophers; i++)
        pthread_mutex_init(&forks[i], NULL);

    init_philosophers(philosophers, forks, number_of_philosophers, routine);

    for (int i = 0; i < number_of_philosophers; i++)
        pthread_join(philosophers[i].thread, NULL);

    for (int i = 0; i < number_of_philosophers; i++)
        pthread_mutex_destroy(&forks[i]);

    free(forks);
    free(philosophers);
    return 0;
}

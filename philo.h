#ifndef PHILO_H
#define PHILO_H


#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct s_rules {
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long start_timer;
    pthread_mutex_t waiter;
    int *forks_available; // 1 if available, 0 if not
} t_rules;

typedef struct s_philosopher {
    int id;
    pthread_t thread;
    t_rules *rules;
} t_philosopher;


void time_init(long *start_timer);
int get_time(long start_timer);

#endif
#ifndef PHILO_H
#define PHILO_H


#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct s_philosopher
{
    int id;
    pthread_t thread;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
}   t_philosopher;


void init_philosophers(t_philosopher *philosophers,pthread_mutex_t *forks ,int n, void *arg);
#endif
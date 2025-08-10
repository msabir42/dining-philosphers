#include "philo.h"

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void time_init(long *start_timer)
{
    struct timeval t_val;
    gettimeofday(&t_val, NULL);
    *start_timer = t_val.tv_sec * 1000L + t_val.tv_usec / 1000L;
}

int get_time(long start_timer)
{
    struct timeval t_val;
    gettimeofday(&t_val, NULL);
    long time = t_val.tv_sec * 1000L + t_val.tv_usec / 1000L - start_timer;
    return (int)time;
}

 
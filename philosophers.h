#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

#define RUN 1

typedef struct s_philosopher
{
    int id;
    pthread_t philosopher;
    pthread_t chek_death;
    int meals_eaten;
    long last_eat_time;
    t_simulation *simulation;
} t_philosophers;

typedef struct s_simulation
{
   	int				number_of_philosophers;
	size_t			count_meal;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	long			start_time;
	int				arg_6;
	int				must_eat;
	int				stop;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_count_meal;
	pthread_mutex_t	mutex_last_eat;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	mutex_start;
	t_philosophers		*philosopher;
} t_simulation;

int	check(int argc, char **argv);
void	put_string(char *str, int fd);
int	    is_number(char *str);
void	error_in_arg(int i);
long	ft_atoil(char *str);
void	init_philo(t_simulation *simulation, int argc, char **argv);
void	routine(void* arg);
long	get_current_time(void);
void	ft_usleep(int ms);
int	check_stop(t_simulation *simulation);
void print_status(t_philosophers *philo, t_simulation *simulation, char *status);
void realease_forks(t_philosophers *philosopher, t_simulation *simulation);
int cycle(t_philosophers *philosopher, t_simulation *simulation);



int is_end_simulation(t_simulation *simulation);

int philosopher_saturation(t_philosophers *philosopher,
                           t_simulation *simulation);
int is_died(t_philosophers *philosopher, t_simulation *simulation);
int printf_status(t_simulation *simulation, t_philosophers *philo);
int create_philosophers(t_simulation *simulation);

int unlock_forks(t_simulation *simulation, t_philosophers *philo);
int odd_case(t_simulation *simulation, t_philosophers *philo);
int even_case(t_simulation *simulation, t_philosophers *philo);
void unlock_lock(t_simulation *simulation, t_philosophers *philo);


#endif
#include "philosophers.h"

int	check(int argc, char **argv)
{
	int	i;

	if (argc == 6 || argc == 5)
	{
		i = 1;
		while (argv[i])
		{
			if (!is_number(argv[i]))
			{
				error_in_arg(i);
				return (0);
			}
			i++;
		}
		if (!chek_max_int(argv))
			return (0);
		return (1);
	}
	else
	{
		put_str("ERROR: The number of argments must be 5 or 6\n", 2);
		return (0);
	}
}

int	main(int ac, char **av)
{
	t_simulation	simulation;
	int		i;

	i = 0;
	if (!check_arg(ac, av))
		return (0);
	init_philo(&simulation, ac, av);
	if (simulation.time_sleep > simulation.time_die)
		simulation.time_sleep = simulation.time_die;
	if (simulation.time_eat > simulation.time_die)
		simulation.time_eat = simulation.time_die;
	init_mutex(&simulation);
	create_thread(&simulation);
	while (i < simulation.nb)
	{
		pthread_join(simulation.philo[i].thread, NULL);
		i++;
	}
	free(simulation.fork);
	free(simulation.philo);
	return (0);
}
#include "philosophers.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < ms)
	{
		usleep(100);
	}
}

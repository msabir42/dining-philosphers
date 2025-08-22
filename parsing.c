#include "philosophers.h"

void	put_string(char *str, int fd)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && (str[i] <= '9' && str[i] >= '0'))
		i++;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (!str[i])
		return (1);
	else
		return (0);
}

void	error_in_arg(int i)
{
	if (i == 1)
		put_string("ERROR: mistake in number_of_philosophers\n", 2);
	else if (i == 2)
		put_string("ERROR :mistake in  time_to_die\n", 2);
	else if (i == 3)
		put_string("ERROR ;mistake in time_to_eat\n", 2);
	else if (i == 4)
		put_string("ERROR: mistake in time_to_sleep\n", 2);
	else
		put_string("ERROR: mistake in number_of_times_each_philosopher_must_eat\n",2);
}

long	ft_atoil(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	chek_max_int(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoil(av[i]) > INT_MAX)
		{
			put_string("all the value must be  less than INT_MAX\n", 2);
			return (0);
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		if (ft_atoil(av[i]) == 0)
		{
			put_string("all value must be more than 0\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msabir <msabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:33:26 by msabir            #+#    #+#             */
/*   Updated: 2025/08/23 15:33:27 by msabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void put_string(char *str, int fd)
{
    int len = 0;
    while (str[len])
        len++;
    write(fd, str, len);
}

int is_number(char *str)
{
    int i = 0;

    if (!str[i])
        return 0;

    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    if (str[i] == '+')
        i++;
    if (!str[i])
        return 0;

    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
        i++;
    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;

    return str[i] ? 0 : 1;
}

void error_in_arg(int i)
{
    if (i == 1)
        put_string("ERROR: mistake in number_of_philosophers\n", 2);
    else if (i == 2)
        put_string("ERROR: mistake in time_to_die\n", 2);
    else if (i == 3)
        put_string("ERROR: mistake in time_to_eat\n", 2);
    else if (i == 4)
        put_string("ERROR: mistake in time_to_sleep\n", 2);
    else
        put_string("ERROR: mistake in number_of_times_each_philosopher_must_eat\n", 2);
}

long ft_atoil(char *str)
{
    long result = 0;
    int i = 0;
    int sign = 1;

    while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-') sign = -1;
        i++;
    }
    while (str[i] && (str[i] >= '0' && str[i] <= '9'))
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

int check_max_int(char *arg)
{
    long num = ft_atoil(arg);
    if (num > INT_MAX || num <= 0)
    {
        put_string("All values must be >0 and <= INT_MAX\n", 2);
        return 0;
    }
    return 1;
}

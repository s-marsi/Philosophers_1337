/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:41:21 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/04 16:39:26 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

size_t	ft_atoi(char *number)
{
	int		i;
	int		n;
	size_t	result;

	n = 10;
	i = 0;
	result = 0;
	if (number[i] == '+')
		i++;
	while (number[i])
	{
		result = (result * n) + ((number[i] - '0'));
		if (result >= INT_MAX)
		{
			write(2, "very large number\n", 19);
			exit (1);
		}
		i++;
	}
	return (result);
}

void	ft_sleeping(int time_to_sleep)
{
	int	current;

	current = get_time();
	while (1)
	{
		if (current + time_to_sleep <= get_time())
			break ;
		usleep(1);
	}
}

int	check_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	return (0);
}

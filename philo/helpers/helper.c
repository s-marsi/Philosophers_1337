/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:05 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/22 16:33:16 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	print_msg(t_philo *philo, char *msg)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->finish_mutex);
	if (check_philos(data, philo))
	{
		pthread_mutex_unlock(&data->finish_mutex);
		return (1);
	}
	printf("%d %d %s\n", my_get_time() \
	- philo->data->time_start, philo->id, msg);
	pthread_mutex_unlock(&data->finish_mutex);
	return (0);
}

int	my_get_time(void)
{
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}

void	ft_sleeping(t_philo *philo, int time_to_sleep)
{
	int	current;

	current = my_get_time();
	while (!check_philos(philo->data, philo))
	{
		if ((current + time_to_sleep) <= my_get_time())
			break ;
		usleep(50);
	}
}

int	check_philos(t_data *data, t_philo *philo)
{
	(void) philo;
	pthread_mutex_lock(&data->die_mutex);
	if (data->is_die != 0)
	{
		pthread_mutex_unlock(&data->die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (0);
}

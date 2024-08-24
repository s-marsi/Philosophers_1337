/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:05 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/24 11:28:31 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	print_msg(t_philo *philo, char *msg)
{
	t_data	*data;

	data = philo->data;
	if (check_philos(philo->data, philo))
		return (1);
	sem_wait(data->finish_sem);
	if (!check_philos(philo->data, philo))
	{
		printf("%d %d %s\n", my_get_time() \
		- philo->data->time_start, philo->id, msg);
		sem_post(data->finish_sem);
		return (0);
	}
	return (1);
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
		usleep(500);
	}
}

int	check_philos(t_data *data, t_philo *philo)
{
	(void) philo;
	sem_wait(data->die_sem);
	if (data->is_die != 0)
	{
		sem_post(data->die_sem);
		return (1);
	}
	sem_post(data->die_sem);
	return (0);
}

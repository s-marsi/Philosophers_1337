/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:46 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/14 19:38:56 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_msg(philo, "has taken fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (philo->num_philos == 1)
	{
		while (!check_philos(philo->data, philo))
			;
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	pthread_mutex_lock(philo->right_fork);
	if (print_msg(philo, "has taken fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		if (philo->num_philos > 1)
			pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf("%d %d is eating\n", my_get_time() \
	- philo->data->time_start, philo->id);
	philo->last_eat = my_get_time();
	return (0);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	if (philo->num_philos > 1)
		pthread_mutex_unlock(philo->right_fork);
}

int	actions(t_philo *philo)
{
	int	time_eat;
	int	time_sleep;

	pthread_mutex_lock(&philo->eat_mutex);
	time_eat = philo->data->time_to_eat;
	time_sleep = philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->eat_mutex);
	if (lock_fork(philo))
		return (1);
	philo->eaten_time++;
	ft_sleeping(philo, time_eat);
	unlock_fork(philo);
	if (print_msg(philo, "is sleeping"))
		return (1);
	ft_sleeping(philo, time_sleep);
	if (print_msg(philo, "is thinking"))
		return (1);
	return (0);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	while (1)
	{
		if (philo->id % 2 == 0)
			usleep(400);
		if (actions(philo))
			return (NULL);
		if (philo->eaten_time == philo->philo_goal)
		{
			pthread_mutex_lock(&philo->data->finish_mutex);
			philo->data->eat_finish++;
			pthread_mutex_unlock(&philo->data->finish_mutex);
			return (NULL);
		}
	}
	return (NULL);
}

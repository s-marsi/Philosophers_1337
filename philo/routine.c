/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:46 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/24 10:07:16 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->num_philos == 1)
	{
		while (!check_philos(philo->data))
			;
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_msg(philo, "has taken fork"))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	if (one_philo(philo))
		return (1);
	pthread_mutex_lock(philo->right_fork);
	if (print_msg(philo, "has taken fork") || print_msg(philo, "is eating"))
	{
		unlock_fork(philo);
		return (1);
	}
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat = my_get_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_sleeping(philo, philo->data->time_to_eat);
	unlock_fork(philo);
	return (0);
}

int	actions(t_philo *philo)
{
	if (lock_fork(philo))
		return (1);
	philo->eaten_time++;
	if (philo->eaten_time == philo->philo_goal)
	{
		pthread_mutex_lock(&philo->data->finish_mutex);
		philo->data->eat_finish++;
		pthread_mutex_unlock(&philo->data->finish_mutex);
	}
	if (print_msg(philo, "is sleeping"))
		return (1);
	ft_sleeping(philo, philo->data->time_to_sleep);
	if (print_msg(philo, "is thinking"))
		return (1);
	return (0);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (TRUE)
	{
		if (actions(philo))
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

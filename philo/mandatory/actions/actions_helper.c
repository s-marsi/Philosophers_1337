/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:06:54 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/04 14:21:21 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	lock_fork(t_philo *philo)
{
	if (philo->philosopher_id == philo->num_philosophers)
	{
		if (lock_1(philo))
			return (1);
	}
	else
	{
		if (lock_2(philo))
			return (1);
	}
	return (0);
}

void	unlock_fork(t_philo *philo)
{
	if (philo->philosopher_id == philo->num_philosophers)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

int	lock_1(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (check_state(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf("%d ms %d has taken a fork\n", \
	get_time() - philo->data->program_start, philo->philosopher_id);
	pthread_mutex_lock(philo->left_fork);
	if (check_state(philo))
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf("%d ms %d has taken a fork\n", \
	get_time() - philo->data->program_start, philo->philosopher_id);
	return (0);
}

int	lock_2(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf("%d ms %d has taken a fork\n", \
	get_time() - philo->data->program_start, philo->philosopher_id);
	pthread_mutex_lock(philo->right_fork);
	if (check_state(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf("%d ms %d has taken a fork\n", \
	get_time() - philo->data->program_start, philo->philosopher_id);
	return (0);
}

int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	if (lock_fork(philo))
		return (1);
	pthread_mutex_lock(philo->eat_mutex);
	if (philo->eat_times >= 0)
		philo->eat_times++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->eat_mutex);
	printf("%d ms %d is eating\n", \
	get_time() - philo->data->program_start, philo->philosopher_id);
	ft_sleeping(philo->data->time_eat);
	unlock_fork(philo);
	return (0);
}

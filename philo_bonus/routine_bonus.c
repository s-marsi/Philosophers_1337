/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:46 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/24 12:48:00 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlock_fork(t_philo *philo)
{
	sem_post(philo->data->forks);
	if (philo->num_philos > 1)
		sem_post(philo->data->forks);
}

int	lock_fork(t_philo *philo)
{
	sem_wait(philo->data->forks);
	if (print_msg(philo, "has taken fork"))
	{
		sem_post(philo->data->forks);
		return (1);
	}
	if (philo->num_philos == 1)
	{
		ft_sleeping(philo, philo->data->time_start);
		unlock_fork(philo);
		return (1);
	}
	sem_wait(philo->data->forks);
	if (print_msg(philo, "has taken fork") || print_msg(philo, "is eating"))
	{
		unlock_fork(philo);
		return (1);
	}
	sem_wait(philo->data->finish_sem);
	philo->last_eat = my_get_time();
	sem_post(philo->data->finish_sem);
	return (0);
}

int	actions(t_philo *philo)
{
	int	time_eat;
	int	time_sleep;

	time_eat = philo->data->time_to_eat;
	time_sleep = philo->data->time_to_sleep;
	if (lock_fork(philo))
		return (1);
	sem_wait(philo->data->finish_sem);
	philo->eaten_time++;
	sem_post(philo->data->finish_sem);
	ft_sleeping(philo, time_eat);
	unlock_fork(philo);
	if (print_msg(philo, "is sleeping"))
		return (1);
	ft_sleeping(philo, time_sleep);
	if (print_msg(philo, "is thinking"))
		return (1);
	return (0);
}

void	*routine(t_philo **philos, t_philo *philo)
{
	t_data	*data;

	pthread_create(&philo->thread, NULL, philos_status, philo);
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(200);
	while (philo->eaten_time != philo->philo_goal)
	{
		if (actions(philo))
		{
			pthread_join(philo->thread, NULL);
			(ft_free(philos, data->num_philos), clean_up(data, philos, 0));
			exit (1);
		}
		usleep (700);
	}
	pthread_join(philo->thread, NULL);
	(ft_free(philos, data->num_philos), clean_up(data, philos, 0));
	exit (0);
	return (NULL);
}

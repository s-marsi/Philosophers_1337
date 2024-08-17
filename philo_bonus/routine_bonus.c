/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:46 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/16 20:38:45 by smarsi           ###   ########.fr       */
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
		while (!check_philos(philo->data, philo))
			;
		unlock_fork(philo);
		return (1);
	}
	sem_wait(philo->data->forks);
	if (print_msg(philo, "has taken fork"))
	{
		unlock_fork(philo);
		return (1);
	}
	printf("%d %d is eating\n", my_get_time() \
	- philo->data->time_start, philo->id);
	philo->last_eat = my_get_time();
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

void	ft_exit(t_philo **philos, t_philo *philo, t_data *data, int status)
{
	pthread_join(philo->thread, NULL);
	(ft_free(philos, data->num_philos), clean_up(data, philos, 0));
	exit (status);
}

void	*routine(t_philo **philos, t_philo *philo)
{
	t_data	*data;

	pthread_create(&philo->thread, NULL, philos_status, philo);
	data = philo->data;
	while (philo->eaten_time != philo->philo_goal)
	{
		if (philo->id % 2 == 0)
			usleep(1500);
		if (actions(philo))
			ft_exit (philos, philo, data, 1);
	}
	ft_exit (philos, philo, data, 0);
	return (NULL);
}

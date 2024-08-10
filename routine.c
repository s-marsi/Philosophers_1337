#include "philo.h"

int	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (check_philos(philo->data, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf("%d ms %d has taken left fork\n", my_get_time() - philo->data->time_start, philo->id);
	pthread_mutex_lock(philo->right_fork);
	if (check_philos(philo->data, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf("%d ms %d has taken right fork\n", my_get_time() - philo->data->time_start, philo->id);
	printf("%d ms %d is eating\n", my_get_time() - philo->data->time_start, philo->id);
	return (0);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
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
	philo->last_eat = my_get_time();
	ft_sleeping(time_eat);
	philo->eaten_time++;
	unlock_fork(philo);
	if (check_philos(philo->data, philo))
		return (1);
	else
		printf("%d ms %d is sleeping\n", my_get_time() - philo->data->time_start, philo->id);
	ft_sleeping(time_sleep);
	if (check_philos(philo->data, philo))
		return (1);
	else
		printf("%d ms %d is thinking\n", my_get_time() - philo->data->time_start, philo->id);
	return (0);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	while (1)
	{
		if (check_philos(philo->data, philo) || actions(philo))
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

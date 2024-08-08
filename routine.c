#include "philo.h"

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	printf("%d ms %d has taken left fork\n", my_get_time() - philo->data->time_start, philo->id);
	pthread_mutex_lock(philo->right_fork);
	printf("%d ms %d has taken right fork\n", my_get_time() - philo->data->time_start, philo->id);
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

	philo->last_eat = my_get_time();
	pthread_mutex_lock(&philo->eat_mutex);
	time_eat = philo->data->time_to_eat;
	time_sleep = philo->data->time_to_sleep;
	pthread_mutex_unlock(&philo->eat_mutex);
	lock_fork(philo);
	pthread_mutex_lock(&philo->data->die_mutex);
	if (philo->data->is_die != 0)
	{
		pthread_mutex_unlock(&philo->data->die_mutex);
		return (1);
	}
	else
		printf("%d ms %d is eating\n", my_get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->die_mutex);
	ft_sleeping(time_eat);
	philo->eaten_time++;
	unlock_fork(philo);
	ft_sleeping(time_sleep);
	pthread_mutex_lock(&philo->data->die_mutex);
	if (philo->data->is_die != 0)
	{
		pthread_mutex_unlock(&philo->data->die_mutex);
		return (1);
	}
	else
		printf("%d ms %d is thinking\n", my_get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->die_mutex);
	return (0);
}

void	*routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *) philosopher;
	while (1)
	{
		pthread_mutex_lock(&philo->data->die_mutex);
		if (philo->data->is_die > 0)
		{
			pthread_mutex_unlock(&philo->data->die_mutex);
			return (NULL);
		}
		if (my_get_time() - philo->last_eat >= philo->data->time_to_die)
		{
			printf("%d ms %d died\n", my_get_time() - philo->data->time_start, philo->id);
			philo->data->is_die = philo->id;
			pthread_mutex_unlock(&philo->data->die_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->die_mutex);
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

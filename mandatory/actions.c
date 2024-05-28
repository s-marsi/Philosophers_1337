#include "philo.h"

void	lock_fork(t_philo *philo)
{
	if (philo->philosopher_id == philo->num_philosophers)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%d ms %d has taken a fork\n", get_time() - philo->data->program_start, philo->philosopher_id);
		pthread_mutex_lock(philo->left_fork);
		printf("%d ms %d has taken a fork\n", get_time() - philo->data->program_start, philo->philosopher_id);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%d ms %d has taken a fork\n", get_time() - philo->data->program_start, philo->philosopher_id);
		pthread_mutex_lock(philo->right_fork);
		printf("%d ms %d has taken a fork\n", get_time() - philo->data->program_start, philo->philosopher_id);
	}
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

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	lock_fork(philo);
	pthread_mutex_lock(philo->eat_mutex);
	if (philo->eat_times >= 0)
		philo->eat_times++;
	philo->last_eat = get_time();
	pthread_mutex_unlock(philo->eat_mutex);
	printf("%d ms %d is eating\n", get_time() - philo->data->program_start, philo->philosopher_id);
	ft_sleeping(philo->data->time_eat);
	unlock_fork(philo);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	printf("%d ms %d is sleeping\n", get_time() - philo->data->program_start, philo->philosopher_id);
	ft_sleeping(philo->data->time_sleep);
}

void	ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->state)
	{
		pthread_mutex_unlock(&philo->data->state_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
	printf("%d ms, %d is thinking\n", get_time() - philo->data->program_start, philo->philosopher_id);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:04:03 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/04 14:19:34 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_eat(t_philo *philo)
{
	if (philo->num_philosophers == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%d ms %d has taken a fork\n", \
		get_time() - philo->data->program_start, philo->philosopher_id);
		while (1)
		{
			if (check_state(philo))
			{
				pthread_mutex_unlock(philo->right_fork);
				return (1);
			}
		}
	}
	if (check_eat(philo))
		return (1);
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	if (!check_state(philo))
		printf("%d ms %d is sleeping\n", \
		get_time() - philo->data->program_start, philo->philosopher_id);
	ft_sleeping(philo->data->time_sleep);
}

void	ft_think(t_philo *philo)
{
	if (!check_state(philo))
		printf("%d ms, %d is thinking\n", \
		get_time() - philo->data->program_start, philo->philosopher_id);
}

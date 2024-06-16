/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:29:06 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/16 14:24:20 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_status_helper(t_data *data, int flag)
{
	if (flag)
	{
		pthread_mutex_lock(&data->state_mutex);
		data->state = 1;
		printf("%d ms all philo has eaten at least %d time \n", \
		get_time() - data->program_start, data->eat_goal);
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	return (0);
}

void	set_state(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->state_mutex);
	data->state = 1;
	pthread_mutex_unlock(&data->state_mutex);
	printf("%d ms %d died \n", \
	get_time() - data->program_start \
	, philo->philosopher_id);
	pthread_mutex_unlock(philo->eat_mutex);
}

void	philos_status(t_data *data, t_philo **philosophers)
{
	int (i), (time_eat), (flag);
	while (1)
	{
		i = 0;
		flag = 1;
		while (i < data->num_philosophers)
		{
			pthread_mutex_lock(philosophers[i]->eat_mutex);
			time_eat = (get_time() - philosophers[i]->last_eat);
			if (philosophers[i]->eat_times < philosophers[i]->philo_goal)
				flag = 0;
			pthread_mutex_unlock(philosophers[i]->eat_mutex);
			if (time_eat > data->time_die)
			{
				set_state(data, philosophers[i]);
				return ;
			}
			i++;
		}
		if (philos_status_helper(data, flag))
			return ;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/10 18:52:28 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers_status(t_data *data, t_philo **philos)
{
	(void) philos;
	while (1)
	{
		pthread_mutex_lock(&data->finish_mutex);
		if (data->eat_finish == data->num_philos)
		{
			data->is_die = -1;
			pthread_mutex_unlock(&data->finish_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->finish_mutex);
		pthread_mutex_lock(&data->die_mutex);
		if (data->is_die > 0)
		{
			pthread_mutex_unlock(&data->die_mutex);
			return ;
		}
		pthread_mutex_unlock(&data->die_mutex);
	}
}

void	philosophers_life(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->threads[i], NULL, routine, philos[i]);
		usleep(50);
		i++;
	}
	philosophers_status(data, philos);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}

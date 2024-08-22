/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/22 16:34:51 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosophers_status(t_data *data, t_philo **philos)
{
	int	i;

	pthread_mutex_lock(&data->finish_mutex);
	while (data->eat_finish != data->num_philos)
	{
		pthread_mutex_unlock(&data->finish_mutex);
		i = 0;
		while (philos[i])
		{
			pthread_mutex_lock(&data->finish_mutex);
			if (my_get_time() - philos[i]->last_eat > data->time_to_die)
			{
				pthread_mutex_lock(&data->die_mutex);
				if (data->eat_finish != data->num_philos)
					printf("%d %d died\n", my_get_time() - data->time_start, philos[i]->id);
				pthread_mutex_unlock(&data->finish_mutex);
				data->is_die = philos[i]->id;
				pthread_mutex_unlock(&data->die_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->finish_mutex);
			i++;
		}
		usleep(100);
		pthread_mutex_lock(&data->finish_mutex);
	}
	pthread_mutex_lock(&data->die_mutex);
	data->is_die = -1;
	pthread_mutex_unlock(&data->die_mutex);
	pthread_mutex_unlock(&data->finish_mutex);
}

void	philosophers_life(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->threads[i], NULL, routine, philos[i]);
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

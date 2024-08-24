/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/24 10:06:29 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	super_visor_continued(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&philos[i]->eat_mutex);
		if (my_get_time() - philos[i]->last_eat > data->time_to_die)
		{
			pthread_mutex_lock(&data->die_mutex);
			printf("%d %d died\n", my_get_time() - \
			data->time_start, philos[i]->id);
			pthread_mutex_unlock(&philos[i]->eat_mutex);
			data->is_die = philos[i]->id;
			pthread_mutex_unlock(&data->die_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philos[i]->eat_mutex);
		i++;
	}
	return (0);
}

void	super_visor(t_data *data, t_philo **philos)
{
	pthread_mutex_lock(&data->finish_mutex);
	while (data->eat_finish != data->num_philos)
	{
		pthread_mutex_unlock(&data->finish_mutex);
		if (super_visor_continued(data, philos))
			return ;
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
	super_visor(data, philos);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
}

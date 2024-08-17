/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:57 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/17 11:25:07 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*philos_status(void	*philosopher)
{
	t_data	*data;
	t_philo	*philo;

	philo = philosopher;
	data = philo->data;
	sem_wait(data->finish_sem);
	while (philo->eaten_time != philo->philo_goal)
	{
		sem_post(data->finish_sem);
		sem_wait(data->die_sem);
		if (data->is_die > 0)
		{
			sem_post(data->die_sem);
			return (NULL);
		}
		sem_post(data->die_sem);
		sem_wait(data->finish_sem);
	}
	sem_post(data->finish_sem);
	return (NULL);
}

static void	philo_life_helper(t_data *data, int status)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status > 0)
		{
			i = 0;
			while (i < data->num_philos)
			{
				kill(data->p_ids[i], SIGKILL);
				i++;
			}
			return ;
		}
		if (status == 0)
			i++;
	}
	printf("%d ms all philo has eaten at least %d time", my_get_time() - \
	data->time_start, data->eat_target);
}

void	philosophers_life(t_data *data, t_philo **philos)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->num_philos)
	{
		data->p_ids[i] = fork();
		if (!data->p_ids[i])
			routine(philos, philos[i]);
		i++;
	}
	i = 0;
	if (data->num_philos == 1)
	{
		waitpid(-1, &status, 0);
		kill(data->p_ids[i], SIGTERM);
	}
	else
		philo_life_helper(data, status);
}

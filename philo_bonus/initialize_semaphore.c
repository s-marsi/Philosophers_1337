/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_semaphore.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 13:42:28 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/16 20:37:27 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	uninitialize_semaphore(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->die_sem);
	sem_close(data->finish_sem);
	unlink("die_sem");
	unlink("finish_sem");
	unlink("forks");
}

static void	handle_sema_error(t_data *data)
{
	if (data->die_sem != SEM_FAILED)
	{
		sem_unlink("die_sem");
		sem_close(data->die_sem);
	}
	if (data->finish_sem != SEM_FAILED)
	{
		sem_unlink("finish_sem");
		sem_close(data->finish_sem);
	}
	if (data->forks != SEM_FAILED)
	{
		sem_unlink("forks");
		sem_close(data->forks);
	}
	ft_putendl("semaphore error\n", 2);
}

int	initialize_semaphore(t_data *data)
{
	sem_unlink("finish_sem");
	sem_unlink("die_sem");
	sem_unlink("forks");
	data->finish_sem = sem_open("finish_sem", O_CREAT | O_EXCL, 0644, 1);
	data->die_sem = sem_open("die_sem", O_CREAT | O_EXCL, 0644, 1);
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->num_philos);
	if (data->finish_sem == SEM_FAILED || data->die_sem == SEM_FAILED
		|| data->forks == SEM_FAILED)
	{
		handle_sema_error(data);
		return (1);
	}
	return (0);
}

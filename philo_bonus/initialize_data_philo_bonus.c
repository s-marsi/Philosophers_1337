/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data_philo_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:01 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/15 19:27:40 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	initialize_data(t_data *data, int ac, char *av[])
{
	(void) ac;
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos == 0)
	{
		ft_putendl("The number of philosophers should be greater than 0.", 2);
		return (1);
	}
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_die = 0;
	data->time_start = my_get_time();
	if (av[5])
		data->eat_target = ft_atoi(av[5]);
	else
		data->eat_target = -1;
	if (data->eat_target == 0)
	{
		ft_putendl("0 ms all philo has eaten at least 0 time", 2);
		return (1);
	}
	if (initialize_semaphore(data))
		return (1);
	return (0);
}

static int	initialize_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->num_philos = data->num_philos;
	philo->data = data;
	philo->eaten_time = 0;
	philo->last_eat = my_get_time();
	philo->philo_goal = data->eat_target;
	return (0);
}

t_philo	**allocate_rsrs(t_data *data, t_philo **philos)
{
	int	i;

	i = 0;
	philos = malloc(data->num_philos * sizeof(t_philo));
	data->p_ids = malloc(data->num_philos * sizeof(pid_t));
	if (!philos || !data->p_ids)
	{
		clean_up(data, philos, 1);
		return (NULL);
	}
	return (philos);
}

t_philo	**create_philos(t_data *data)
{
	t_philo	**philos;
	int		i;

	i = 0;
	philos = NULL;
	philos = allocate_rsrs(data, philos);
	if (!philos)
		return (NULL);
	while (i < data->num_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			(ft_free(philos, i), clean_up(data, philos, 1));
			return (NULL);
		}
		if (initialize_philo(data, philos[i], i))
			return (NULL);
		i++;
	}
	return (philos);
}

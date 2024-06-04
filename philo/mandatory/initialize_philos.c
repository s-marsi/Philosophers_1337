/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_philos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:39:18 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/04 14:40:58 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	initialize_fork(t_data *data, t_philo **philosophers)
{
	int	i;

	(void) philosophers;
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

static t_philo	**allocate_phil_rsc(t_data **data)
{
	t_philo	**philosophers;

	philosophers = malloc((*data)->num_philosophers * sizeof(t_philo));
	(*data)->thread = malloc((*data)->num_philosophers * \
	sizeof(pthread_t));
	(*data)->forks = malloc((*data)->num_philosophers * \
	sizeof(pthread_mutex_t));
	if (!philosophers || !(*data)->thread || !(*data)->forks)
		clean_up(data, philosophers, 1);
	return (philosophers);
}

void	initialize_data(t_data *data, int ac, char *av[])
{
	data->num_philosophers = ft_atoi(av[1]);
	if (!data->num_philosophers)
		ft_error("num of philo should be more that 0.\n", 0);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->eat_goal = ft_atoi(av[5]);
		if (!data->eat_goal)
		{
			printf("%d ms all philo has eaten at least %d time \n"\
			, 0, data->eat_goal);
			exit (0);
		}
	}
	else
		data->eat_goal = -1;
	data->state = 0;
	data->program_start = get_time();
}

void	create_philo_helper(t_data *data, t_philo **philos, int i)
{
	philos[i]->philo_goal = data->eat_goal;
	if (data->eat_goal == -1)
		philos[i]->eat_times = -2;
	else
		philos[i]->eat_times = 0;
	if (i == data->num_philosophers - 1)
		philos[i]->right_fork = &data->forks[0];
	else
		philos[i]->right_fork = &data->forks[i + 1];
	philos[i]->philosopher_id = i + 1;
	philos[i]->left_fork = &data->forks[i];
	philos[i]->eat_mutex = malloc(sizeof(pthread_mutex_t));
	if (!philos[i]->eat_mutex)
	{
		ft_free(philos, data->num_philosophers, i);
		clean_up(&data, philos, 1);
	}
	philos[i]->data = data;
	philos[i]->last_eat = get_time();
	philos[i]->num_philosophers = data->num_philosophers - 1;
	pthread_mutex_init(philos[i]->eat_mutex, NULL);
}

t_philo	**create_philosophers(t_data *data)
{
	t_philo	**philos;
	int		i;

	philos = allocate_phil_rsc(&data);
	initialize_fork(data, philos);
	pthread_mutex_init(&data->state_mutex, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i])
		{
			ft_free(philos, data->num_philosophers, 0);
			clean_up(&data, philos, 1);
		}
		create_philo_helper(data, philos, i);
		i++;
	}
	return (philos);
}

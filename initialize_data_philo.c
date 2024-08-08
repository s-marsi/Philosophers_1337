#include "philo.h"

int	initialize_data(t_data *data, int ac, char *av[])
{
	(void) ac;
	data->num_philos = ft_atoi(av[1]);
	if (data->num_philos == 0)
	{
		ft_putendl("num of philo should be more than 0", 2);
		return (1);
	}
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->is_die = 0;
	data->eat_finish = 0;
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
	pthread_mutex_init(&data->finish_mutex, NULL);
	pthread_mutex_init(&data->die_mutex, NULL);
	return (0);
}

static int	initialize_philo(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_init(&philo->eat_mutex, NULL);
	
	if (i == data->num_philos - 1)
	{
		philo->left_fork = &data->forks[0];
		philo->right_fork = &data->forks[i];
	}
	else
	{
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[i + 1];
	}
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
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	data->threads = malloc(data->num_philos * sizeof(pthread_t));
	philos = malloc(data->num_philos * sizeof(t_philo));
	if (!data->threads || !philos || !data->forks)
	{
		clean_up(&data, philos, 1);
		return (NULL);
	}
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (philos);
}

t_philo	**create_philos(t_data *data)
{
	t_philo	**philos;
	int	i;

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
			(ft_free(philos, i), clean_up(&data, philos, 1));
			return (NULL);
		}
		if (initialize_philo(data, philos[i], i))
			return (NULL);
		i++;
	}
	return (philos);
}

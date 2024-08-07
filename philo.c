#include "philo.h"

static int	check_args(int ac, char	*av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

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
	if (av[5])
		data->eat_target = ft_atoi(av[5]);
	else
		data->eat_target = -1;
	if (data->eat_target == 0)
	{
		ft_putendl("0 ms all philo has eaten at least 0 time", 2);
		return (1);
	}
	return (0);
}

int	create_philos(t_data *data, t_philo ***philos)
{
	t_philo	**philos_tmp;

	philos_tmp = *philos;
	data->forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	data->threads = malloc(data->num_philos * sizeof(pthread_t));
	philos_tmp = malloc(data->num_philos * sizeof(t_philo));
	if (!data->threads || !philos_tmp || !data->forks)
	{
		clean_up(&data, philos_tmp, 1);
		return (1);
	}
	clean_up(&data, philos_tmp, 0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_philo	**philos;

	if (ac != 5 && ac != 6)
	{
		ft_putendl("args should be >= 5", 2);
		return (1);
	}
	if (check_args(ac, av) || initialize_data(&data, ac, av))
		return (1);
	data.is_die = 0;
	data.eat_count = 0;
	if (create_philos(&data, &philos))
		return (1);
	ft_print(data);
	ft_putendl("###### finish #########", 1);
	return (0);
}

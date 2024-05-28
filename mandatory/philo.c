#include "philo.h"

void	*actions_call(void *philosopher)
{
	t_philo *philo;
	int	i = 0;

	philo = (t_philo *) philosopher;
	while (1)
	{
			if (ft_eat(philo) == 1)
				return (NULL);
			ft_sleep(philo);
			ft_think(philo);
		i++;
	}
	return (NULL);
}

void	philosopher_life(t_data *data, t_philo **philosophers)
{
	int		i;

	i = 0;
	
	while (i < data->num_philosophers)
	{
		pthread_create(&data->thread[i], NULL, actions_call, philosophers[i]);
		usleep(50);
		i++;
	}
	philos_status(data, philosophers);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
	uninitialize_rscs(data);
	ft_free(philosophers, data->num_philosophers, data->num_philosophers);
	clean_up(&data, philosophers, 0);
}

int	main(int ac, char *av[])
{
	t_data data;
	t_philo **philos;

	check_params(ac, av);
	initialize_data(&data, ac, av);
	philos = create_philosophers(&data);
	philosopher_life(&data, philos);
	printf("end");
	return (0);
}
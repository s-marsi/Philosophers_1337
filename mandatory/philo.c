#include "philo.h"

void	*actions_call(void *philosopher)
{
	t_philo *philo;
	int	i = 0;

	philo = (t_philo *) philosopher;
	while (1)
	{
			ft_eat(philo);
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
}

int	main(int ac, char *av[])
{
	t_data data;
	t_philo **philos;

	check_params(ac, av);
	initialize_data(&data, ac, av);
	philos = create_philosophers(&data);
	philosopher_life(&data, philos);
	return (0);
}
#include "../philo.h"

void	clean_up(t_data **data, t_philo **philos, int flag)
{
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
	if ((*data)->threads)
	{
		free((*data)->threads);
		(*data)->threads = NULL;
	}
	if ((*data)->forks)
	{
		free((*data)->forks);
		(*data)->forks = NULL;
	}
	if (flag)
		printf("error malloc.\n");
}

void	ft_free(t_philo **philos, int num_phil)
{
	int	i;

	if (philos == NULL)
		return ;
	i = 0;
	while (i < num_phil)
	{
		if (philos[i])
		{
			// free(philos[i]->eat_mutex);
			free(philos[i]);
			philos[i] = NULL;
		}
		i++;
	}
}

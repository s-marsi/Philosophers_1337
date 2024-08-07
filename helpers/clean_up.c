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

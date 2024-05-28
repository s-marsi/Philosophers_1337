#include "philo.h"

void	clean_up(t_data **data, t_philo **philosophers, int flag)
{
	if (philosophers)
	{
		free(philosophers);
		philosophers = NULL;
	}
	if ((*data)->thread)
	{
		free((*data)->thread);
		(*data)->thread = NULL;
	}
	if ((*data)->forks)
	{
		free((*data)->forks);
		(*data)->forks = NULL;
	}
	if (flag)
	{
		printf("error malloc.\n");
		exit(1);
	}
}
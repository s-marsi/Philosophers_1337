#include "philo.h"

void	uninitialize_rscs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
        pthread_detach(data->thread[i]);
		i++;
	}
}

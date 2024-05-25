#include "philo.h"

void	philos_status_helper(t_data *data, t_philo **philosophers, int flag)
{
    if (flag)
	{
		printf("%d ms all philo has eaten at least %d time \n", get_time() - data->program_start\
		, data->eat_goal);
		uninitialize_rscs(data);
		ft_free(philosophers, data->num_philosophers, data->num_philosophers);
		clean_up(&data, philosophers, 0);
		exit (0) ;
	}
}

void	philos_status(t_data *data, t_philo **philosophers)
{
	int (i), (time_eat), (flag);
	while (1)
	{
		i = 0;
		flag = 1;
		while (i < data->num_philosophers)
		{
			pthread_mutex_lock(philosophers[i]->eat_mutex);
			time_eat = (get_time() - philosophers[i]->last_eat);
			if (time_eat >= data->time_die)
			{
				printf("%d ms %d died \n", get_time() - data->program_start\
				,philosophers[i]->philosopher_id);
				uninitialize_rscs(data);
				ft_free(philosophers, data->num_philosophers, data->num_philosophers);
				clean_up(&data, philosophers, 0);
				exit (0);
			}
			if (philosophers[i]->eat_times < philosophers[i]->philo_goal)
				flag = 0;
			pthread_mutex_unlock(philosophers[i]->eat_mutex);
			i++;
		}
		philos_status_helper(data, philosophers, flag);
	}
}
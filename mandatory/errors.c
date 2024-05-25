#include "philo.h"

void	ft_error(char *msg, int status)
{
	printf("%s\n", msg);
	exit (status);
}

void    ft_free(t_philo **philosophers, int num_phil, int num_mutex)
{
    int i;

 	if (philosophers == NULL)
        return;
	i = 0;
    while (i < num_phil)
    {
        if (i < num_mutex)
        {
            free(philosophers[i]->eat_mutex);
            philosophers[i]->eat_mutex = NULL;
        }
        free(philosophers[i]);
        philosophers[i] = NULL;
        i++;
    }
}

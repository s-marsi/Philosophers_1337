#include "../philo.h"

int	my_get_time(void)
{
	struct timeval s_time;

	gettimeofday(&s_time , NULL);
	return ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000));
}

void	ft_sleeping(int time_to_sleep)
{
	int	current;

	current = my_get_time();
	while (1)
	{
		if (current + time_to_sleep <= my_get_time())
			break ;
		usleep(1);
	}
}

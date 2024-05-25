#include "philo.h"

int	get_time(void)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

size_t	ft_atoi(char *number)
{
	int	i;
	int	n;
	size_t	result;

	n = 10;
	i = 0;
	result = 0;
	if (number[i] == '+')
		i++;
	while (number[i])
	{
		result = (result * n) + ((number[i] - '0')); 
		i++;
	}
	return (result);
}

void	ft_sleeping(int time_to_sleep)
{
	int	current = get_time();
	while(1)
	{
		if (current + time_to_sleep <= get_time())
			break;
		usleep(1);
	}
}

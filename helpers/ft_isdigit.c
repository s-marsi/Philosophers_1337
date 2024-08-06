#include "../philo.h"

int	ft_isdigit(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	ft_putendl("number should content only digit", 2);
	return (0);
}

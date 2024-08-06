#include "philo.h"

static int	check_args(int ac, char	*av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int philo(int ac, char *av[])
{
	(void) ac;
	(void) av;
	return (0);
}

int	main(int ac, char *av[])
{
	if (ac != 5 && ac != 6)
	{
		ft_putendl("args should be >= 5", 2);
		return (1);
	}
	if (check_args(ac, av))
		return (1);
	if (philo(ac, av))
		return (1);
	return (0);
}

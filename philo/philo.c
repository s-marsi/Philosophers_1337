/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:39 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/11 12:26:38 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int ac, char	*av[])
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	data;
	t_philo	**philos;
	t_data	*data_tmp;

	philos = NULL;
	if (ac != 5 && ac != 6)
	{
		ft_putendl("args should be >= 5", 2);
		return (1);
	}
	if (check_args(ac, av) || initialize_data(&data, ac, av))
		return (1);
	philos = create_philos(&data);
	if (!philos)
		return (1);
	philosophers_life(&data, philos);
	if (data.is_die == -1)
		printf("all philos eat at least %d time\n", data.eat_target);
	data_tmp = &data;
	(ft_free(philos, data.num_philos), clean_up(&data_tmp, philos, 0));
	return (0);
}

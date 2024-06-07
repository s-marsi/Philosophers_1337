/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:42:41 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/05 10:41:42 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	is_valid_number(int ac, char *av[])
{
	int (i), (j);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '-')
		{
			printf("argument number : %d", i);
			printf(", should not be a negative number\n");
			exit(0);
		}
		else if (av[i][j] == '+')
			j++;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("argument number : %d", i);
				printf(", should be a valid number\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	check_params(int ac, char *av[])
{
	char	*msg;

	msg = NULL;
	if (ac != 5 && ac != 6)
	{
		msg = "params should be between 5 and 6.";
		ft_error(msg, 0);
	}
	is_valid_number(ac, av);
}

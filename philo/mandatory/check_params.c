/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:42:41 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/16 12:06:25 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_minus(char c, int i)
{
	if (c == '-')
	{
		printf("argument number : %d", i);
		printf(", should not be a negative number\n");
		return (1);
	}
	return (0);
}
static int	check_empty(char c, int i)
{
	if (!c)
	{
		printf("argument number : %d", i);
		printf(", should be a valid number\n");
		return (1);
	}
	return (0);
}

static int	is_valid_number(int ac, char *av[])
{
	int (i), (j);
	i = 1;
	while (i < ac)
	{
		j = 0;
		if (check_minus(av[i][j], i))
			return (1);
		else if (av[i][j] == '+')
			j++;
		if (check_empty(av[i][j], i))
			return (1);
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
			{
				printf("argument number : %d", i);
				printf(", should be a valid number\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_params(int ac, char *av[])
{
	char	*msg;

	msg = NULL;
	if (ac != 5 && ac != 6)
	{
		msg = "params should be between 5 and 6.\n";
		write(2, msg, 35);
		return (1);
	}
	if (is_valid_number(ac, av))
		return (1);
	if (ft_atoi(av[1]) == 0)
	{
		msg = "num of philo should be more that 0.\n";
		write(2, msg, 37);
		return (1);
	}
	return (0);
}

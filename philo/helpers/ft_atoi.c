/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:19 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/10 18:47:28 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static int	check_error(char *str, int *index)
{
	int	i;

	i = *index;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
	{
		ft_putendl("number should be positive", 2);
		return (1);
	}
	if (str[i] == '+')
		i++;
	if (!ft_isdigit(str[i]))
		return (1);
	*index = i;
	return (0);
}

int	ft_atoi(char *str)
{
	size_t	number;
	int		i;

	number = 0;
	i = 0;
	if (check_error(str, &i))
		return (1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		if (number >= INT_MAX)
		{
			write(2, "very large number\n", 19);
			return (-1);
		}
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
	{
		ft_putendl("number should content only digit", 2);
		return (-1);
	}
	return (number);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:42:55 by smarsi            #+#    #+#             */
/*   Updated: 2024/06/16 12:10:36 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_data **data, t_philo **philosophers, int flag)
{
	if (philosophers)
	{
		free(philosophers);
		philosophers = NULL;
	}
	if ((*data)->thread)
	{
		free((*data)->thread);
		(*data)->thread = NULL;
	}
	if ((*data)->forks)
	{
		free((*data)->forks);
		(*data)->forks = NULL;
	}
	if (flag)
		printf("error malloc.\n");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:22 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/16 20:39:06 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	clean_up(t_data *data, t_philo **philos, int flag)
{
	uninitialize_semaphore(data);
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
	if (data->p_ids)
		free(data->p_ids);
	if (flag)
		printf("error malloc.\n");
}

void	ft_free(t_philo **philos, int num_phil)
{
	int	i;

	if (philos == NULL)
		return ;
	i = 0;
	while (i < num_phil)
	{
		if (philos[i])
		{
			free(philos[i]);
			philos[i] = NULL;
		}
		i++;
	}
}

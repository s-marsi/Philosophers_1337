/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:45:15 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/14 13:38:19 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	ft_isdigit(int nb)
{
	if (nb >= '0' && nb <= '9')
		return (1);
	ft_putendl("number should content only digit", 2);
	return (0);
}

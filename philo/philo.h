/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:52 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/22 15:53:18 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
#define TRUE 1
typedef struct s_data
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	die_mutex;
	pthread_mutex_t	finish_mutex;
	pthread_t		*threads;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_target;
	int				is_die;
	int				eat_finish;
	int				time_start;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	eat_mutex;
	t_data			*data;
	int				num_philos;
	int				id;
	int				eaten_time;
	int				last_eat;
	int				philo_goal;
}	t_philo;

void	ft_putendl(char *str, int fd);
int		ft_isdigit(int nb);
int		ft_atoi(char *str);
void	clean_up(t_data **data, t_philo **philos, int flag);
int		print_msg(t_philo *philo, char *msg);
void	ft_free(t_philo **philos, int num_phil);
int		my_get_time(void);
void	ft_sleeping(t_philo *philo, int time_to_sleep);
int		check_philos(t_data *data, t_philo *philo);
void	*routine(void *philosopher);
int		initialize_data(t_data *data, int ac, char *av[]);
t_philo	**create_philos(t_data *data);
void	philosophers_life(t_data *data, t_philo **philos);
#endif

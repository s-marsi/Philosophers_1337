/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarsi <smarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 18:44:52 by smarsi            #+#    #+#             */
/*   Updated: 2024/08/15 19:27:18 by smarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <signal.h>
# define EXIT_DEAD 1
# define EXIT_ALIVE 0

typedef struct s_data
{
	sem_t	*forks;
	sem_t	*die_sem;
	sem_t	*finish_sem;
	pid_t	*p_ids;
	int		num_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		eat_target;
	int		is_die;
	int		time_start;
}	t_data;

typedef struct s_philo
{
	t_data		*data;
	pthread_t	thread;
	int			num_philos;
	int			id;
	int			eaten_time;
	int			last_eat;
	int			philo_goal;
}	t_philo;

void	ft_putendl(char *str, int fd);
int		ft_isdigit(int nb);
int		ft_atoi(char *str);
void	clean_up(t_data *data, t_philo **philos, int flag);
int		print_msg(t_philo *philo, char *msg);
void	ft_free(t_philo **philos, int num_phil);
int		my_get_time(void);
void	ft_sleeping(t_philo *philo, int time_to_sleep);
int		check_philos(t_data *data, t_philo *philo);
void	*routine(t_philo **philos, t_philo *philo);
int		initialize_data(t_data *data, int ac, char *av[]);
t_philo	**create_philos(t_data *data);
void	philosophers_life(t_data *data, t_philo **philos);
int		initialize_semaphore(t_data *data);
void	uninitialize_semaphore(t_data *data);
void	*philos_status(void	*philosopher);
#endif

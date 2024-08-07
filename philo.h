# ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct	s_data
{
	pthread_mutex_t *forks;
	pthread_mutex_t die_mutex;
	pthread_t		*threads;
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_target;
	int				is_die;
	int				eat_count;
}	t_data;

typedef struct	s_philo
{
	pthread_mutex_t left_fork;
	pthread_mutex_t right_fork;
	pthread_mutex_t	eat_mutex;
	t_data			*data;
    int				eaten_time;
	int				last_eat;
	int				philo_goal;
}	t_philo;


void	ft_putendl(char *str, int fd);
int	    ft_isdigit(int nb);
int     ft_atoi(char *str);
void	clean_up(t_data **data, t_philo **philos, int flag);
void    ft_print(t_data data);
# endif
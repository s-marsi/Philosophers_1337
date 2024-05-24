# ifndef PHILO_H
# define PHILO_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
typedef struct	s_data
{

    int             num_philosophers;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             eat_goal;
    int             program_start;
    pthread_mutex_t *forks;
    pthread_mutex_t *threads;
    pthread_t       *thread;
}	t_data;
typedef struct	s_philo
{
    int             num_philosophers;
    int             philosopher_id;
    int             philo_goal;
    int             eat_times;
    int             last_eat;
    t_data          *data;
    pthread_mutex_t *eat_mutex;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
}	t_philo;
void	ft_error(char *params, char *msg, int status);
void	check_params(int ac, char *av[]);
// void	ft_is_digit(int ac, char *av[]);
// size_t	ft_atoi(char *number);
// void	initialize_fork(t_data *data, t_philo **philosophers);
// void	lock_fork(t_philo *philosopher);
// void	unlock_fork(t_philo *philosopher);
// void	ft_eat(t_philo *philo);
// void	ft_think(t_philo *philo);
// void	ft_sleep(t_philo *philo);
// int	    get_time(void);
// void	ft_sleeping(int time_to_sleep);
// void	ft_free(t_data *data, t_philo **philosophers);
// void	uninitialize_fork(t_data *data);
// void	uninitialize_thread(t_data *data);
# endif
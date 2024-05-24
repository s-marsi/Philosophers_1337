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
    pthread_mutex_t *threads_mutex;
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
void	ft_error(char *msg, int status);
void	clean_up(t_data **data, t_philo **philosophers, int flag);
void    ft_free(t_philo **philosophers, int num_phil, int num_mutex);
void	ft_msg(char *msg1, char *msg2, int arg1, int arg2);
void	check_params(int ac, char *av[]);
size_t	ft_atoi(char *number);
int	    get_time(void);
void	ft_sleeping(int time_to_sleep);
void	initialize_data(t_data *data, int ac, char *av[]);
t_philo	**create_philosophers(t_data *data);
void	philos_status(t_data *data, t_philo **philosophers);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void    uninitialize_rscs(t_data *data);
# endif
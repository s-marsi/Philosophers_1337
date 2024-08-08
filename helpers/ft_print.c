#include "../philo.h"

void    ft_print(t_data data, t_philo **philos)
{
    int i;

    i = 0;
    printf("################  DATA INFO ################\n");
    printf("num_of_philos => %d\n", data.num_philos);
    printf("time_to_die => %d\n", data.time_to_die);
    printf("time_to_eat => %d\n", data.time_to_eat);
    printf("time_to_sleep => %d\n", data.time_to_sleep);
    printf("time_target => %d\n", data.eat_target);
    printf("eat_finish => %d\n", data.eat_finish);
    printf("\n################  PHILOS INFO ################\n");
    while (i < data.num_philos && philos[i])
    {
        printf("          ######## PHILO %d INFO #######        \n",(i + 1));
        printf("eat_count => %d\n", philos[i]->eaten_time);
        printf("last_eat => %d\n", philos[i]->last_eat);
        printf("philo_goal => %d\n", philos[i]->philo_goal);
        i++;
    }
    
}

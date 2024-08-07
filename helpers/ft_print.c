#include "../philo.h"

void    ft_print(t_data data)
{
    printf("################  DATA INFO ################\n");
    printf("num_of_philos => %d\n", data.num_philos);
    printf("time_to_die => %d\n", data.time_to_die);
    printf("time_to_eat => %d\n", data.time_to_eat);
    printf("time_to_sleep => %d\n", data.time_to_sleep);
    printf("time_target => %d\n", data.eat_target);
    printf("eat_count => %d\n", data.eat_count);
    printf("\n################  PHILOS INFO ################\n");
    
}

#include "../philo.h"

static int	check_error(char *str, int *index)
{
	int	i;

	i = *index;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
    if (str[i] == '-')
    {
        ft_putendl("number should be positive", 2);
        return (1);
    }
    if (str[i] == '+')
        i++;
    if (!ft_isdigit(str[i]))
		return (1);
	*index = i;
	return (0);
}

int ft_atoi(char *str)
{
    size_t  number;
    int     i;

	number = 0;
    i = 0;
	if (check_error(str, &i))
		return (1);
    
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++; 
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
        i++;
	if (str[i])
	{
		ft_putendl("number should content only digit", 2);
		return (1);
	}
	return (0);
}

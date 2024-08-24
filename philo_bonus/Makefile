CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

CC = cc 

NAME = philo_bonus

FILES = philo_bonus.c routine_bonus.c initialize_data_philo_bonus.c philo_life_bonus.c initialize_semaphore.c \
		helpers/ft_putendl_bonus.c helpers/ft_atoi_bonus.c helpers/ft_isdigit_bonus.c \
		helpers/clean_up_bonus.c helpers/helper_bonus.c\

FILES_O = $(FILES:.c=.o) 

$(NAME) : $(FILES_O)
	$(CC) $(CFLAGS) $(FILES_O) -o $(NAME)

all : $(NAME)

clean :
	rm -f $(FILES_O)

fclean : clean
	rm -f $(NAME)

re : fclean all

.SECONDARY : $(FILES_O)

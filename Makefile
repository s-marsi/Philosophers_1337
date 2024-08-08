CFLAGS = -Wall -Wextra -Werror  -g3 -fsanitize=thread

CC = cc 

NAME = philo

FILES = philo.c routine.c initialize_data_philo.c philo_life.c\
		helpers/ft_putendl.c helpers/ft_atoi.c helpers/ft_isdigit.c helpers/clean_up.c helpers/ft_print.c helpers/helper.c\

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


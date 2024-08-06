CFLAGS = -Wall -Wextra -Werror -fsanitize=address

CC = cc 

NAME = philo

FILES = philo.c helpers/ft_putendl.c helpers/ft_atoi.c helpers/ft_isdigit.c

FILES_O = $(FILES:.c=.o) 

$(NAME) : $(FILES_O)
	$(CC) $(CFLAGS) $(FILES_O) -o $(NAME)

clean :
	rm -f $(FILES_O)

fclean : clean
	rm -f $(NAME)

.SECONDARY : $(FILES_O)


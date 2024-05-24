CFLAGS = -Wall -Wextra -Werror  #-fsanitize=thread 

CC = cc

NAME = philo

SRC = mandatory/philo.c mandatory/errors.c mandatory/check_params.c mandatory/philo_threads.c\
# mandatory/helpers.c mandatory/forks.c mandatory/uninitialize.c mandatory/actions/eat.c  
#mandatory/actions/sleep.c  mandatory/actions/think.c 

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all : $(NAME)

re : fclean all

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f philo

.SECONDARY : $(OBJ)
CFLAGS = -Wall -Wextra -Werror   -fsanitize=thread 
#-fsanitize=address 
CC = cc

NAME = philo

SRC = mandatory/philo.c mandatory/errors.c mandatory/check_params.c mandatory/initialize_philos.c \
	mandatory/helpers.c mandatory/philos_status.c mandatory/clean_up.c mandatory/actions.c mandatory/uninitialize.c

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
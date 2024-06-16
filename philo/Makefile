CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

CC = cc

NAME = philo

SRC = mandatory/philo.c mandatory/check_params.c mandatory/helpers.c mandatory/initialize_philos.c mandatory/clean_up.c mandatory/uninitialize.c \
	mandatory/philos_status.c  mandatory/actions/actions.c mandatory/actions/actions_helper.c 

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
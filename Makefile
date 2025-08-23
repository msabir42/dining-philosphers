NAME := philo
CC := cc
CFLAGS := -Wall -Wextra -Werror -pthread
SRC := main.c checkers.c time.c mutexes.c routine.c parsing.c init_philosophers.c odd_even.c strategy.c realese.c 
OBJ := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

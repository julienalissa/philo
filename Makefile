NAME = philo
CFLAGS = -g -Wall -Wextra -Werror
CC = cc

SRCS := philo.c utils.c
OBJS := ${SRCS:.c=.o}

HEADER := philo.h

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re

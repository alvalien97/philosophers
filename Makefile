NAME = philo
OBJS = ${SRCS:.c=.o}
SRCS = main.c init.c routine.c utils.c monitor.c

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
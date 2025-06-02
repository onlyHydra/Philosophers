NAME = philo
NAME_BONUS = philo_bonus

INCLUDE = -Iheader 
LIBS = imports


CC = gcc
CFLAG = -Wall -Wextra -Werror -g -pthread

SRCS = $(shell find srcs -type f -name "*.c")
OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAG) $(OBJS)  -o $(NAME)

%.o:%.c
	$(CC) $(CFLAG) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all


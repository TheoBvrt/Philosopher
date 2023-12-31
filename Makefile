NAME = philo
SRCS = src/main.c src/init.c src/log.c src/philo_behaviour.c src/utils.c src/philo_behaviour_2.c
OBJS = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o : src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@

clean:
	$(RM) -r obj/*

fclean: clean
	$(RM) $(NAME)

re: fclean all
FILES = src/main.c src/coder_routine.c src/destroy.c src/dongles.c src/donglesv2.c src/free.c src/heap.c src/heapv2.c src/helpers.c src/init_helpers.c src/init.c src/monitor.c src/parser.c src/simulation_main.c src/time.c src/utils.c src/init_helpers2.c
HEADER = src/codexion.h
NAME = codexion

OBJS = $(FILES:.c=.o)
all: $(NAME)

$(NAME): $(OBJS)
	cc -Wall -Wextra -Werror -pthread $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -Wall -Wextra -Werror -pthread -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.phony: clean
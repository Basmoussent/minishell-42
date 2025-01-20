CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wunused -Wextra -g3
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:src/%.c=build/%.o)
EXEC = minishell
LIBFT = libft/libft.a

all: $(EXEC)

$(EXEC): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(EXEC)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

clean:
	make -C libft fclean
	rm -rf build

fclean: clean
	rm -f $(EXEC)

re: fclean all

norm:
	@bash ./utils/norm_it.sh

.PHONY: all clean fclean re

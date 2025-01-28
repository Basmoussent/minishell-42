CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wunused -Wextra -g3 
LIB_FLAGS = -lreadline
SRC = $(shell find src -name '*.c')
OBJ = $(SRC:src/%.c=build/%.o)
EXEC = minishell
LIBFT = libft/libft.a

all: $(EXEC)

$(EXEC): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(EXEC) $(LIB_FLAGS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	make -C libft fclean
	rm -rf build

fclean: clean
	rm -f $(EXEC)

re: fclean all

norm:
	@bash ./utils/norm_it.sh

.PHONY: all clean fclean re norm

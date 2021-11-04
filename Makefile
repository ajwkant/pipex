NAME = pipex
SRCS =	pipex.c
OBJ = $(SRCS:%.c=%.o)
FLAGS = -Wall -Wextra -Werror
LIBFTLIBRARY = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(OBJ) $(FLAGS) $(LIBFTLIBRARY) -o $(NAME)

clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all
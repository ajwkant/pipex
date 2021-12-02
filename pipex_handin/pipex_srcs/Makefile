NAME = pipex
SRCS =	pipex.c path_access.c parse_and_helperfunctions.c \
		error.c
SRCS_BONUS =	./bonus/pipex_bonus.c path_access.c \
				parse_and_helperfunctions.c error.c
OBJ = $(SRCS:%.c=%.o)
FLAGS = -Wall -Wextra -Werror -I$(HEADERFILE)
LIBFTLIBRARY = ./libft/libft.a
HEADERFILE = .
VPATH = ./pipex_srcs
CC = gcc

ifdef BONUS
SRCS = $(SRCS_BONUS)
NAME = pipex_bonus
HEADERFILE = ./bonus_srcs
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./libft
	$(CC) $(OBJ) $(FLAGS) $(LIBFTLIBRARY) -o $(NAME)

bonus:
	$(MAKE) BONUS=1 all

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

fclean_bonus:
	$(MAKE) BONUS=1 fclean

re: fclean all

bonus_re:
	$(MAKE) BONUS=1 re

.PHONY: all bonus clean fclean fclean_bonus re bonus_re

SOURCES =	pipex.c pipex_utils.c errorhandling.c commands.c

OBJECTS =	$(SOURCES:.c=.o)

LIBFT_PATH =./libft
LIBFT =		$(LIBFT_PATH)/libft.a

NAME =	pipex

CC = gcc

FLAGS = -Wall -Werror -Wextra

RM 	= rm -f

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o) -I $(LIBFT_PATH)

all:	$(NAME) $(LIBFT)

$(NAME):	$(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean:
		$(MAKE) -C $(LIBFT_PATH) clean
		$(RM) $(OBJECTS)

fclean:		clean
			$(MAKE) -C $(LIBFT_PATH) fclean
			$(RM) $(NAME)

re:	fclean	all

.PHONY: all $(NAME) clean fclean re

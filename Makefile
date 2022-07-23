SOURCES =			pipex.c pipex_utils.c errorhandling.c

SOURCES_BONUS =		pipex_bonus.c pipex_utils_bonus.c
SOURCES_BONUS +=	errorhandling_bonus.c commands_bonus.c
SOURCES_BONUS +=	pipes_bonus.c

OBJECTS =	$(SOURCES:.c=.o)
OBJECTS_BONUS =	$(SOURCES_BONUS:.c=.o)

LIBFT_PATH =./libft
LIBFT =		$(LIBFT_PATH)/libft.a

NAME =	pipex

NAME_BONUS = pipex_bonus

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

RM 	= rm -f

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o) -I $(LIBFT_PATH)

all:	$(NAME) $(LIBFT)

$(NAME):	$(OBJECTS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

$(NAME_BONUS): $(OBJECTS_BONUS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJECTS_BONUS) $(LIBFT) -o $(NAME_BONUS)

bonus:	$(NAME_BONUS)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJECTS)
	$(RM) $(OBJECTS_BONUS)

fclean:		clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re:	fclean	all

.PHONY: all clean fclean re

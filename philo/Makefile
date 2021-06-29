SRC			= main.c validate_arg.c \
			philo_thread.c start.c time_ms.c utils_libft.c \




_GREEN		=\e[32m
_YELLOW		=\e[33m

NAME 		= philo

OBJ			= $(SRC:.c=.o)

HEADER 		= philo.h
CC 			= gcc
CFLAGS 		= -Wall -Werror -Wextra

all: 		$(NAME)

$(NAME): 	$(OBJ) $(HEADER)
			$(CC) -o $(NAME) $(OBJ)
			@printf "$(_GREEN)\t\t✓✓✓	COMPILATION!	✓✓✓$(_GREEN)\n"

clean:
			@rm -f $(OBJ)
			@printf "$(_YELLOW)\t\t✓✓✓	CLEAN!	✓✓✓$(_YELLOW)\n"

fclean: 	clean
	 		@rm -f $(NAME)

re: 		fclean all

norm:
			Norminette -R CheckForbiddenSourcrHeader $(SRC) $(HEADER)
			@printf "$(_GREEN)\t\t✓✓✓	NORMINETTE!	✓✓✓$(_GREEN)\n"

.PHONY:		all clean fclean re norm
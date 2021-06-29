SRC			= main_bonus.c validate_arg_bonus.c \
			philo_thread_bonus.c start_bonus.c time_ms.c utils_libft.c \




_GREEN		=\e[32m
_YELLOW		=\e[33m

NAME 		= philo_bonus

OBJ			= $(SRC:.c=.o)

HEADER 		= philo_bonus.h
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
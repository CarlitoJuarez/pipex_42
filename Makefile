NAME 			= pipex

CC	 			= gcc

FLAGS 			= -Wall -Wextra -Werror

RM				= rm -rf

HEADER			= pipex.h


# MANDATORY
DIR_MANDATORY 	= mandatory/
SRC_MANDATORY 	= pipex.c
PATH_MANDATORY	= $(addprefix $(DIR_MANDATORY), $(SRC_MANDATORY))
OBJ_MANDATORY	= $(PATH_MANDATORY:.c=.o)

# BONUS
DIR_BONUS 		= bonus/
SRC_BONUS	 	= pipex_bonus.c
PATH_BONUS		= $(addprefix $(DIR_BONUS), $(SRC_BONUS))
OBJ_BONUS		= $(PATH_BONUS:.c=.o)

# UTILS
DIR_UTILS		= utils/
SRCS_UTILS		= utils_1.c utils_2.c util_gnl.c util_split.c exec_cmnd.c util_flags_paths.c
PATH_UTILS		= $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
OBJ_UTILS		= $(PATH_UTILS:.c=.o)

# COMMANDS
%.o: %.c 	$(HEADER) Makefile
							@${CC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJ_UTILS) $(OBJ_MANDATORY)
							@$(CC) $(OBJ_UTILS) $(OBJ_MANDATORY) -o $(NAME)


all:		$(NAME)

bonus:		$(OBJ_UTILS) $(OBJ_BONUS)
							@$(CC) $(OBJ_UTILS) $(OBJ_BONUS) -o $(NAME)

clean:						
							@$(RM)	$(OBJ_MANDATORY)
							@$(RM)	$(OBJ_UTILS)
							@$(RM)	$(OBJ_BONUS)

fclean:		clean
							@$(RM) $(NAME)

re:							fclean all

.PHONY: 	all clean fclean bonus re
NAME 			= so_long

CC	 			= cc

FLAGS 			= -Wall -Wextra -Werror -g

RM				= rm -rf

HEADER			= so_long.h

LINKING			= -I/usr/include -Imlx

MLX_FLAGS		= -Lmlx -lmlx -lXext -lX11

# MAIN
DIR_MAIN	 	= ./
SRC_MAIN	 	= so_long.c
PATH_MAIN		= $(addprefix $(DIR_MAIN), $(SRC_MAIN))
OBJ_MAIN		= $(PATH_MAIN:.c=.o)

# UTILS
DIR_UTILS		= utils/
SRCS_UTILS		= utils_1.c make_move.c
PATH_UTILS		= $(addprefix $(DIR_UTILS), $(SRCS_UTILS))
OBJ_UTILS		= $(PATH_UTILS:.c=.o)


# COMMANDS
%.o: %.c 	$(HEADER) Makefile
							@${CC} ${FLAGS} -c $< -o $@ 
# $< $(LINKING)

$(NAME):	$(OBJ_UTILS) $(OBJ_MAIN)
							@$(CC) $(OBJ_UTILS) $(OBJ_MAIN) -o $(NAME) $(MLX_FLAGS)

all:		$(NAME)

clean:						
							@$(RM)	$(OBJ_MAIN)
							@$(RM)	$(OBJ_UTILS)

fclean:		clean
							@$(RM) $(NAME)

re:							fclean all

.PHONY: 	all clean fclean re

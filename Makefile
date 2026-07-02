NAME		=	minishell

CCFLAGS		=	-Wall -Wextra -Werror

CC		=	clang

HEADERS		=	./inc/

SRC_PATH	=	./src/

OBJ_PATH	=	./obj/

SRCS		=	main.c \
			signal_func.c \
			signal_func2.c \
			cleaning.c \
			cleaning2.c \
			replace_by_int.c \
			expand_norm.c \
			expand_norm2.c \
			expand_utils.c \
			expand_utils2.c \
			expand.c \
			parsing_help.c \
			parsing_help2.c \
			parsing_help3.c \
			ft_split_quotes.c \
			parsing.c \
			io_utils.c \
			io.c \
			edit_env_utils.c \
			edit_env_utils2.c \
			edit_env.c \
			builtins_utils.c \
			builtins.c \
			exec_utils.c \
			exec_utils2.c \
			exec_utils3.c \
			exec.c

OBJ			=	${SRCS:.c=.o}

OBJS		=	$(addprefix $(OBJ_PATH), $(OBJ))

LIBFT_DIR	=	./libft/

LIBFT		=	./libft/libft.a

all:		${OBJ_PATH} ${NAME}

${NAME}:	${LIBFT} ${OBJS}
			$(CC) ${CCFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${OBJ_PATH}%.o:	${SRC_PATH}%.c ${HEADERS}
			$(CC) ${CCFLAGS} -I${HEADERS} -c $< -o $@

${OBJ_PATH}:
			@mkdir ${OBJ_PATH}

${LIBFT}:	
			make -C ${LIBFT_DIR} all

clean:
			make -C ${LIBFT_DIR} clean
			rm -rf ${OBJ_PATH}

fclean:		clean
			make -C ${LIBFT_DIR} fclean
			rm -f ${NAME}
 
re:			fclean all
 
.PHONY:		all clean fclean re
